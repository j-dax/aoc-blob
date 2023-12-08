from dataclasses import dataclass


def parse_input(filename) -> list[list[int]]:
    ints = []
    with open(filename, 'r+') as fi:
      for line in fi.readlines():
        if ":" in line:
          ints.append([])
        found = list(map(int,
          filter(lambda x: len(list(
            filter(str.isdigit, x)
          )) > 0,
          line.split(" "))
        ))
        if len(found) > 0:
          ints[-1].extend(found)
    return ints

@dataclass
class TRange:
  left: int
  right: int
  index: int

  def __in__(self, other: int):
    return self.left <= other <= self.right

  def intersect(self, a):
    return TRange(left=max(self.left, a.left), right=min(self.right, a.right), index=a.index)

  def __str__(self):
    return f"TRange({self.left}, {self.right})"

@dataclass
class TUnit:
  destination: TRange
  source: TRange

  def translate(self, tr):
    out = TRange(tr.left, tr.right, tr.index)
    out.left += self.destination.left - self.source.left
    out.right += self.destination.right - self.source.right
    return out 


def solve_a(nums: list[list[int]]):
  queue = [*map(lambda x: TRange(left=x, right=x, index=0), nums[0])]
  groups = [[TUnit(
    destination=TRange(left=nums[i][j], right=nums[i][j] + nums[i][j+2], index=i),
    source=TRange(left=nums[i][j+1], right=nums[i][j+1] + nums[i][j+2], index=i),
  ) for j in range(0, len(nums[i]), 3)] for i in range(1, len(nums))]
  while queue[0].index < len(groups):
    front = queue[0]
    queue = queue[1:]
    group = groups[front.index]
    front.index += 1
    matched = False
    for tr in group:
      inter = front.intersect(tr.source)
      if inter.left <= inter.right:
        queue.append(tr.translate(inter))
        matched = True
    if not matched:
      queue.append(front)
  return min(queue, key=lambda x: x.left).left


def prepare_groups(nums):
  groups = [
    [TUnit(
      destination=TRange(left=nums[i][j], right=nums[i][j]+nums[i][j+2]-1, index=i),
      source=TRange(left=nums[i][j+1], right=nums[i][j+1]+nums[i][j+2]-1, index=i),
      ) for j in range(0, len(nums[i]), 3)
    ] for i in range(1, len(nums))
  ]
  for i in range(len(groups)):
    groups[i] = sorted(groups[i], key=lambda x: x.source.right)
    groups[i] = sorted(groups[i], key=lambda x: x.source.left)
  return groups


def solve_b_next_queue(queue: list[TRange], group: list[TUnit]):
  for _ in range(len(queue)):
    front = queue[0]
    queue = queue[1:]
  
    front.index += 1
    left_min = front.left
    # make sure the input range is covered
    for tr in filter(lambda x: x.source.right >= front.left, group):
      inter = front.intersect(tr.source)
      if inter.left <= inter.right:
        queue.append(tr.translate(inter))
        if left_min < inter.left:
          queue.append(TRange(left=left_min, right=inter.left-1, index=inter.index))
        left_min = max(left_min, inter.right) + 1
    if left_min < front.right:
      queue.append(TRange(left=left_min, right=front.right, index=front.index))
  # merge overlap in resulting queue
  queue.sort(key=lambda x: x.right)
  queue.sort(key=lambda x: x.left)
  for i in range(len(queue)-1,0,-1):
    inter = queue[i].intersect(queue[i-1])
    if inter.left <= inter.right or queue[i].right + 1 == queue[i-1].left or queue[i].left == queue[i-1].right+1:
      queue[i].left = min(queue[i].left, queue[i-1].left)
      queue[i].right = max(queue[i].right, queue[i-1].right)
      queue = queue[:i-1] + queue[i:]

  return queue


def solve_b(nums: list[list[int]]) -> int:
  queue = [
    TRange(left=nums[0][i], right=nums[0][i]+nums[0][i+1]-1, index=0)
    for i in range(0, len(nums[0]), 2)
  ]
  groups = prepare_groups(nums)
  for group in groups:
    queue = solve_b_next_queue(queue, group)
  return min(queue, key=lambda x: x.left).left


def full_test():
  aoc_input = parse_input("test.txt")
  ans = solve_a(aoc_input)
  assert ans == 35, f"Expected 35, got {ans}"
  ans = solve_b(aoc_input)
  assert ans == 46, f"Expected 46, got {ans}"

  aoc_input = parse_input("input.txt")
  ans = solve_a(aoc_input)
  assert ans == 240320250, f"Expected 240320250, got {ans}"
  ans = solve_b(aoc_input)
  assert ans == 28580589, f"Expected 11787590, got {ans}"

if __name__ == "__main__":
  full_test()

