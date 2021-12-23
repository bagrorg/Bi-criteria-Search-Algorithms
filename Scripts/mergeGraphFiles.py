import sys
def main(arg1, arg2, arg3, arg4):
    file_time_name = arg1
    file_dist_name = arg2
    file_coords_name = arg3
    file_output_name = arg4

    file_time = open(file_time_name, 'r')
    file_dist = open(file_dist_name, 'r')
    file_coords = open(file_coords_name, 'r')

    v_count = 0
    a_count = 0
    edges = {}
    vertexes = {}

    for line in file_coords.readlines():
        if line[0] == 'v':
            line = line.strip().split(' ')
            vertexes[int(line[1])] = (line[2], line[3])

    for line_t, line_d in zip(file_time.readlines(), file_dist.readlines()):
        if line_t[0] == 'p':
            line = line_t.strip().split(' ')
            v_count = line[2]
            a_count = line[3]
        elif line_t[0] == 'a':
            line_t = line_t.strip().split(' ')
            line_d = line_d.strip().split(' ')
            id1 = int(line_t[1])
            id2 = int(line_t[2])

            cost_t = line_t[3]
            cost_d = line_d[3]

            edges[(id1, id2)] = (cost_t, cost_d)

    file_time.close()
    file_dist.close()

    res_file = open(file_output_name, 'w')

    res_file.write('p sp ' + str(v_count) + ' ' + str(a_count) + '\n')

    for v in vertexes:
        res_file.write('v ' + str(v - 1) + ' ' + str(vertexes[v][0]) + ' ' + str(vertexes[v][1]) + '\n')

    for e in edges:
        res_file.write('a ' + str(e[0] - 1) + ' ' + str(e[1] - 1) + ' ' + str(edges[e][0]) + ' ' + str(edges[e][1]) + '\n')

    res_file.close()

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])