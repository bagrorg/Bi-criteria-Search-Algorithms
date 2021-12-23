import sys
from PIL import Image, ImageDraw
from tqdm import tqdm

file_history_name = sys.argv[1]
file_graph_name = sys.argv[2]
file_output_name = sys.argv[3]
start_id = int(sys.argv[4])
goal_id = int(sys.argv[5])
duration = int(sys.argv[6])
max_frames = int(sys.argv[7])
w = int(sys.argv[8])
h = int(sys.argv[9])
if duration == -1:
    duration = 200

history = []
nodes = []
edges = []

if w == -1:
    w = 1000
if h == -1:
    h = 1000
margin = 0.05
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
            ids = []
            pred = None
            for id_ in map(int, line.strip().split()[1:]):
                ids.append(id_)
            if line[0] == 'n':
                history[-1][0].append(ids)
            else:
                history[-1][1].append(ids)


def transform(i, j):
    i = w * (1 - 2 * margin) * (i - min_x) / (max_x - min_x)
    i = i + margin * w
    j = h * (1 - 2 * margin) * (j - min_y) / (max_y - min_y)
    j = j + margin * h
    return i, j


def draw_node(draw, i, j, color):
    draw.point((i, j), fill=color)


def draw_edge(draw, i, j, i2, j2, color):
    draw.line((i, j, i2, j2), fill=color, width=1)


def draw_path(draw, path, color):
    pred_i, pred_j = None, None
    for i in path:
        i, j = nodes[i]
        i, j = transform(i, j)
        draw_node(draw, i, j, color)
        if pred_i is not None:
            draw_edge(draw, i, j, pred_i, pred_j, color)
        pred_i = i
        pred_j = j


images = []
default_color = 'grey'
open_path_color = 'orange'
solution_color = 'green'

images.append(Image.new('RGB', (w, h), color='white'))
draw_base = ImageDraw.Draw(images[0])

for u, v in edges:
    x, y = nodes[u]
    x, y = transform(x, y)
    x2, y2 = nodes[v]
    x2, y2 = transform(x2, y2)
    draw_edge(draw_base, x, y, x2, y2, default_color)

for x, y in nodes:
    x, y = transform(x, y)
    draw_node(draw_base, x, y, 'black')

x, y = nodes[start_id]
x, y = transform(x, y)
sz = 1
draw_base.rectangle((x - sz, y - sz, x + sz, y + sz), fill='green')
x, y = nodes[goal_id]
x, y = transform(x, y)
sz = 1
draw_base.rectangle((x - sz, y - sz, x + sz, y + sz), fill='red')

all_solutions = []
group = 1 if max_frames == -1 else 1 + len(history) // max_frames
cur = 0
for open_paths, solutions_paths in tqdm(history):
    cur = (cur + 1) % group
    if cur == 0:
        im = images[-1].copy()
    else:
        im = images[-1]
    draw_im = ImageDraw.Draw(im)

    for cur_path in open_paths:
        draw_path(draw_im, cur_path, open_path_color)

    all_solutions.extend(solutions_paths)
    if cur == 0:
        images.append(im)
    if (cur + 1) % group == 0:
        for cur_path in all_solutions:
            draw_path(draw_im, cur_path, solution_color)
        x, y = nodes[start_id]
        x, y = transform(x, y)
        sz = 1
        draw_im.rectangle((x - sz, y - sz, x + sz, y + sz), fill='green')
        x, y = nodes[goal_id]
        x, y = transform(x, y)
        sz = 1
        draw_im.rectangle((x - sz, y - sz, x + sz, y + sz), fill='red')

draw_im = ImageDraw.Draw(images[-1])
for cur_path in all_solutions:
    draw_path(draw_im, cur_path, solution_color)
x, y = nodes[start_id]
x, y = transform(x, y)
sz = 1
draw_im.rectangle((x - sz, y - sz, x + sz, y + sz), fill='green')
x, y = nodes[goal_id]
x, y = transform(x, y)
sz = 1
draw_im.rectangle((x - sz, y - sz, x + sz, y + sz), fill='red')

for _ in range(3000 // duration):
    images.append(images[-1].copy())

images[0].save(file_output_name, save_all=True, append_images=images[1:], optimize=False, duration=duration, loop=0)
