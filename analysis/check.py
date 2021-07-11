import sys

def main():
  if len(sys.argv) == 2:
    fname = sys.argv[1] 
  else:
    print("Invalid usage.")
    return
  f = open(fname)
  countLapsed(f)

def countLapsed(f):
  previous = None
  lapsed = 0
  for line in f:
    if previous is not None and previous > int(line):
      print(previous)
      lapsed += 1
    previous = int(line)
  print(lapsed)


if __name__ == "__main__":
  main()