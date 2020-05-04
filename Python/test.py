import math

num = 928947511
k= [19245, 19241]
# guess = 4
# lowest_val = math.ceil(math.log(num,guess))
# rem = 3
# while not math.sqrt(rem).is_integer():
#     guess = int(math.pow(4, lowest_val))
#     rem = guess % num
#     lowest_val += 1
#     print(lowest_val)
# print(rem)
v = k[0] * k[1] / num
print(k[1] * k[0] / (v))