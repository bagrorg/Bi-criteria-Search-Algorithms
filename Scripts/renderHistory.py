import sys
from PIL import Image, ImageDraw

file_history_name = sys.argv[1]
file_graph_name = sys.argv[2]
file_output_name = sys.argv[3]

history = []
nodes = []
edges = []

w, h = 1000, 1000
min_x, max_x, min_y, max_y = None, None, None, None

with open(file_graph_name, 'r') as file_graph:
    for line in file_graph:
        if line[0] == 'p':
            n = int(line.split()[2])
            nodes = [None] * n
        elif line[0] == 'v':
            v, x, y = list(map(int, line.split()[1:]))
            nodes[v] = (x, y)
            if min_x is None or min_x > x:
                min_x = x
            if min_y is None or min_y > y:
                min_y = y
            if max_x is None or max_x < x:
                max_x = x
            if max_y is None or max_y < y:
                max_y = y
        elif line[0] == 'a':
            v, u = line.split()[1:3]
            v = int(v)
            u = int(u)
            edges.append((v, u))

with open(file_history_name, 'r') as file_history:
    for line in file_history:
        if len(line.strip()) == 0:
            continue
        if line[0] == 'e':
            history.append(([], []))
        else:
            positions = []
            pred = None
            for coord in map(int, line.strip().split()[1:]):
                if pred is None:
                    pred = coord
                else:
                    positions.append((pred, coord))
                    pred = None
            if line[0] == 'p':
                history[-1][0].append(positions)
            else:
                history[-1][1].append(positions)


def transform(i, j):
    return w * (i - min_x) / (max_x - min_x), h * (j - min_y) / (max_y - min_y)


def draw_node(draw, i, j, color):
    draw.point((i, j), fill=color)


def draw_edge(draw, i, j, i2, j2, color):
    draw.line((i, j, i2, j2), fill=color, width=1)


def draw_path(draw, path, color):
    pred_i, pred_j = None, None
    for i, j in path:
        i, j = transform(i, j)
        if pred_i is not None:
            draw_edge(draw, i, j, pred_i, pred_j, color)
        pred_i = i
        pred_j = j


images = []
default_color = 'grey'
open_path_color = 'orange'
solution_color = 'green'
for open_paths, solutions_paths in [([], [])] + history:
    im = Image.new('RGB', (w, h), color='white')
    draw_im = ImageDraw.Draw(im)

    for u, v in edges:
        x, y = nodes[u]
        x, y = transform(x, y)
        x2, y2 = nodes[v]
        x2, y2 = transform(x2, y2)
        draw_edge(draw_im, x, y, x2, y2, default_color)

    for x, y in nodes:
        x, y = transform(x, y)
        draw_node(draw_im, x, y, 'black')

    for cur_path in open_paths:
        draw_path(draw_im, cur_path, open_path_color)

    for cur_path in solutions_paths:
        draw_path(draw_im, cur_path, solution_color)

    images.append(im)

images[0].save(file_output_name, save_all=True, append_images=images[1:], optimize=False, duration=200, loop=0)
