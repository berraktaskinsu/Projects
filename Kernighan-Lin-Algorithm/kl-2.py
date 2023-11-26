import sys
import time
import numpy as np
from scipy.io import mmread
import networkx as nx
from itertools import count
from networkx.utils import not_implemented_for, py_random_state, BinaryHeap
from networkx.algorithms.community.community_utils import is_partition

__all__ = ["kernighan_lin_bisection"]

def generate_graph_from_mtx(file_path: str, mtx_comment='%') -> nx.Graph:
    with open(file_path, 'r') as file:
        lines = file.readlines()

    while lines[0][0] == mtx_comment:
        lines.pop(0)

    edges = [[int(i) for i in line.split() if i.isdigit()] for line in lines]
    sizes = edges.pop(0)

    G = nx.Graph()
    G.add_nodes_from(range(1, sizes[0]))
    G.add_edges_from(edges)
    return G


def compute_cutsize(G: nx.Graph, partition=None) -> int:
    if partition is None:
        v = G.number_of_nodes()
        partition = kernighan_lin_bisection(G, partition=(range(1, 1 + v//2),
                                                              range(1 + v//2, 1 + v)))
    return sum([len([nb for nb in G.neighbors(node) if nb in partition[1]])
                for node in partition[0]])

def _kernighan_lin_sweep(edges, side):
    costs0, costs1 = costs = BinaryHeap(), BinaryHeap()
    for u, side_u, edges_u in zip(count(), side, edges):
        cost_u = sum(w if side[v] else -w for v, w in edges_u)
        costs[side_u].insert(u, cost_u if side_u else -cost_u)

    def _update_costs(costs_x, x):
        for y, w in edges[x]:
            costs_y = costs[side[y]]
            cost_y = costs_y.get(y)
            if cost_y is not None:
                cost_y += 2 * (-w if costs_x is costs_y else w)
                costs_y.insert(y, cost_y, True)

    i = totcost = 0
    while costs0 and costs1:
        u, cost_u = costs0.pop()
        _update_costs(costs0, u)
        v, cost_v = costs1.pop()
        _update_costs(costs1, v)
        totcost += cost_u + cost_v
        yield totcost, i, (u, v)
        i += 1


@py_random_state(4)
@not_implemented_for("directed")
def kernighan_lin_bisection(G, partition=None, max_iter=10, weight="weight", seed=None):
    n = len(G)
    labels = list(G)
    seed.shuffle(labels)
    index = {v: i for i, v in enumerate(labels)}

    if partition is None:
        side = [0] * (n // 2) + [1] * ((n + 1) // 2)
    else:
        try:
            A, B = partition
        except (TypeError, ValueError) as e:
            raise nx.NetworkXError("partition must be two sets") from e
        if not is_partition(G, (A, B)):
            raise nx.NetworkXError("partition invalid")
        side = [0] * n
        for a in A:
            side[index[a]] = 1

    if G.is_multigraph():
        edges = [
            [
                (index[u], sum(e.get(weight, 1) for e in d.values()))
                for u, d in G[v].items()
            ]
            for v in labels
        ]
    else:
        edges = [
            [(index[u], e.get(weight, 1)) for u, e in G[v].items()] for v in labels
        ]

    for i in range(max_iter):
        costs = list(_kernighan_lin_sweep(edges, side))
        min_cost, min_i, _ = min(costs)
        if min_cost >= 0:
            break

        for _, _, (u, v) in costs[: min_i + 1]:
            side[u] = 1
            side[v] = 0

    A = {u for u, s in zip(labels, side) if s == 0}
    B = {u for u, s in zip(labels, side) if s == 1}
    return A, B

def calculateCutsize(graph, groupA, groupB):
    cutsize = 0
    for (v1, v2) in graph.edges:
        if(v1 in groupA and v2 in groupB):
            cutsize += 1
        elif(v1 in groupB and v2 in groupA):
            cutsize += 1
    return cutsize

graph = generate_graph_from_mtx(sys.argv[1])
start = time.time()
A, B = kernighan_lin_bisection(graph)
print("Cutsize: " + str(calculateCutsize(graph, A, B)))
end = time.time()
print("Duration: " + str(end-start) + " sec")
