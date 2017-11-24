from random import randint
import argparse

parser = argparse.ArgumentParser(description='Graph generator.')
parser.add_argument('-v', type=int, help='Number of verticles')
parser.add_argument('-e', type=int, help='Number of edges')
parser.add_argument('-w', default=10, type=int, help='Max weight')
args = parser.parse_args()

if args.e > args.v * (args.v - 1):
    raise Exception("Can't construct graph with {v} verticles and {e} edges (too many edges)".format(v=args.v, e=args.e))


print(1)
print("{v} {e}".format(v=args.v, e=args.e))

connectionsMap = {}

for i in range(args.e):
    while True:
        v1 = randint(1, args.v)
        v2 = randint(1, args.v)
        while v1 == v2:
            v2 = randint(1, args.v)

        e = (v1, v2)
        e2 = (v2, v1)

        if e not in connectionsMap:
            if e2 not in connectionsMap:
                connectionsMap[e] = randint(1, args.w)
                break



for k,v in connectionsMap.items():
    print("{} {} {}".format(k[0], k[1], v))

startVerticleIndex = randint(1, args.v)
print("{}".format(startVerticleIndex))
