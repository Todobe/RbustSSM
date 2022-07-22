import json
import gzip
import os

import argparse

userIDCount = 0
userIDMap = {}

itemIDCount = 0
itemIDMap = {}


def getUserID(reviewerID):
    global userIDCount
    if reviewerID not in userIDMap:
        userIDMap[reviewerID] = userIDCount
        userIDCount = userIDCount + 1
    return userIDMap[reviewerID]


def getItemID(asin):
    global itemIDCount
    if asin not in itemIDMap:
        itemIDMap[asin] = itemIDCount
        itemIDCount = itemIDCount + 1
    return itemIDMap[asin]


def parse(path):
    """parse json.gz file"""
    g = gzip.open(path, 'rb')
    for l in g:
        yield json.loads(l.decode())


def get_time_stamp(tmStr):
    Comma = tmStr.index(',')
    return int(tmStr[Comma+2:]+tmStr[0:2]+tmStr[3:Comma])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='dataGenerator')

    parser.add_argument('--data_path', default="Video_Games.json.gz", type=str, help='data path')
    parser.add_argument('--meta_data_path', default="meta_Video_Games.json.gz", type=str, help='meta data path')
    parser.add_argument('--output_file', default="./Video_game_network.txt", type=str, help='output file')
    parser.add_argument('--task_file', default="./Video_game_task.txt", type=str, help='task file' )
    parser.add_argument('--big_user_bound', default=5, type=str, help='big user bound')
    args = parser.parse_args()

    user_buy = {}  # 'user' -> [('item','time')]
    edges_weight = {}  # item edge -> weight
    item_user = {}  # {'item: ['user']}
    big_user_cnt = 0
    edge_num = 0
    for d in parse(args.meta_data_path):
        itemID = getItemID(d['asin'])
        for also_buy in d['also_buy']:
            edges_weight[(itemID, getItemID(also_buy))] = 0

    for d in parse(args.data_path):
        userID = getUserID(d['reviewerID'])
        itemID = getItemID(d['asin'])
        if userID in user_buy:
            user_buy[userID].append((itemID, get_time_stamp(d['reviewTime'])))
        else:
            user_buy[userID] = [(itemID, get_time_stamp(d['reviewTime']))]
        if len(user_buy[userID]) == args.big_user_bound * 2:
            big_user_cnt = big_user_cnt + 1
        if itemID in item_user:
            item_user[itemID].append(userID)
        else:
            item_user[itemID] = [userID]

    for user in user_buy:
        user_buy[user].sort(key=lambda x: x[1])

    item_buy_count = [0]*itemIDCount
    for item_times in user_buy.values():
        for item_time in item_times:
            item_buy_count[item_time[0]] = item_buy_count[item_time[0]] + 1

    for i in range(0, itemIDCount):
        edges_weight[(i, i)] = 0
        if i not in item_user:
            item_user[i] = []

    for edge in edges_weight:
        if edge[0] == edge[1]:
            edges_weight[edge] = len(item_user[edge[0]]) / userIDCount
        else:
            edges_weight[edge] = len([val for val in item_user[edge[0]] if val in item_user[edge[1]]]) / len(item_user[edge[0]])
        if edges_weight[edge] != 0:
            edge_num = edge_num + 1

    if not os.path.exists(os.path.dirname(args.output_file)):
        os.makedirs(os.path.dirname(args.output_file))
    if not os.path.exists(os.path.dirname(args.task_file)):
        os.makedirs(os.path.dirname(args.task_file))

    with open(args.output_file, "w") as file:
        file.write(f"{itemIDCount} {edge_num}\n")
        for edge in edges_weight:
            weight = edges_weight[edge]
            if weight != 0:
                file.write(f"{edge[0]} {edge[1]} {weight}\n")
        file.close()

    with open(args.task_file, "w") as file:
        file.write(f"{big_user_cnt}\n")
        for item_stamps in user_buy.values():
            item_num = len(item_stamps)
            if item_num < args.big_user_bound * 2:
                continue
            file.write(f"{item_num} {args.big_user_bound} ")
            for item_stamp in item_stamps:
                file.write(f"{item_stamp[0]} ")
            file.write("\n")
        file.close()
