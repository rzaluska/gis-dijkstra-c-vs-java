from random import randint
import argparse
import itertools
import tempfile
import mmap
import random

parser = argparse.ArgumentParser(description='Graph generator.')
parser.add_argument('-v', type=int, help='Number of verticles')
parser.add_argument('-e', type=int, help='Number of edges')
parser.add_argument('-w', default=10, type=int, help='Max weight')
args = parser.parse_args()

if args.e > args.v * (args.v - 1) // 2:
    raise Exception("Can't construct graph with {v} verticles and {e} edges (too many edges)".format(v=args.v, e=args.e))


all_e = []
for e in itertools.combinations(range(args.v), 2):
    all_e.append((e[0], e[1]))

random.shuffle(all_e)

print(1)
print("{v} {e}".format(v=args.v, e=args.e))

for i in range(args.e):
    line = all_e[i]
    print("{} {} {}".format(line[0] + 1, line[1] + 1, randint(1, args.w)))

startVerticleIndex = randint(1, args.v)
print("{}".format(startVerticleIndex))
