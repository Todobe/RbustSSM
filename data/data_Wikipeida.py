import os
import argparse

from collections import defaultdict

articleID = {}
articleCount = 0


def getArticleID(articleName):
    global articleCount
    if articleName not in articleID:
        articleID[articleName] = articleCount
        articleCount = articleCount + 1
    return articleID[articleName]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='dataGenerator')

    parser.add_argument('--links_file', default="./wikispeedia_paths-and-graph/links.tsv", type=str,
                        help='links file path')
    parser.add_argument('--paths_file', default="./wikispeedia_paths-and-graph/paths_finished.tsv", type=str, help='paths file path')
    parser.add_argument('--output_file', default="./wikispeedia_network.txt", type=str, help='output file')
    parser.add_argument('--task_file', default="./wikispeedia_task.txt", type=str, help='task file')
    args = parser.parse_args()

    links = []
    click_count = defaultdict(int)
    move_count = defaultdict(int)
    edge_weight = defaultdict(float)
    paths = []

    text = ''
    with open(args.paths_file, 'r') as f:
        text = f.read()

    lines = text.split('\n')

    for line in lines:
        if len(line) <= 0 or line[0] == '#':
            continue
        line = line.split('\t')
        path = line[3].split(';')
        article0 = getArticleID(path[0])
        paths.append([article0])
        idx = len(paths) - 1
        for i in range(1, len(path)):
            article1 = getArticleID(path[i-1])
            article2 = getArticleID(path[i])
            click_count[article1] += 1
            move_count[(article1, article2)] += 1
            paths[idx].append(article2)

    for article_pair in move_count:
        edge_weight[article_pair] = move_count[article_pair] / click_count[article_pair[0]]

    if not os.path.exists(os.path.dirname(args.output_file)):
        os.makedirs(os.path.dirname(args.output_file))
    if not os.path.exists(os.path.dirname(args.task_file)):
        os.makedirs(os.path.dirname(args.task_file))

    with open(args.output_file, "w") as file:
        edge_num = len(edge_weight)
        file.write(f"{articleCount} {edge_num}\n")
        for edge in edge_weight:
            weight = edge_weight[edge]
            if weight != 0:
                file.write(f"{edge[0]} {edge[1]} {weight}\n")
        file.close()

    with open(args.task_file, "w") as file:
        paths_len = len(paths)
        file.write(f"{paths_len}\n")
        for path in paths:
            path_len = len(path)
            file.write(f"{path_len} ")
            for article in path:
                file.write(f"{article} ")
            file.write("\n")
        file.close()

    print(len(edge_weight), len(paths))




