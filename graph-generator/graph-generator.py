from random import randint
import random
import argparse
import itertools

parser = argparse.ArgumentParser(description='Graph generator.')
parser.add_argument('-v', type=int, help='Number of verticles')
parser.add_argument('-e', type=int, help='Number of edges')
parser.add_argument('-w', default=10, type=int, help='Max weight')
args = parser.parse_args()

if args.e > (args.v * (args.v - 1)) // 2:
    raise Exception("Can't construct graph with {v} verticles and {e} edges (too many edges)".format(v=args.v, e=args.e))


print(1)
print("{v} {e}".format(v=args.v, e=args.e))

connectionsMap = {}

all_edges = itertools.combinations(range(args.v),2)

p = args.e / ((args.v * (args.v - 1))//2)

printed = 0

last_v = 0

for e in all_edges:
    if random.random() < p:
        print("{} {} {}".format(e[0], e[1], randint(1, args.w)))
        last_v = e[1]
        printed+=1
        if printed == args.e:
            break

startVerticleIndex = randint(1, last_v)
print("{}".format(startVerticleIndex))
