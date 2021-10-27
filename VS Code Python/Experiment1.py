import random
import string
import re


# 1、编写代码：利用 if 判断来制作一个猜数字的小游戏
# 问题描述：程序运行时，系统在指定范围内生成一个随机数字，然后用户
# 进行猜测，并根据用户输入进行必要的提示（right, too large, too small），
# 如果猜对则提前结束程序，如果未有猜对，提示游戏结束并给出正确答案。
def fun1():
    ran = random.randint(0, 1000)
    x = input("请输入猜测的数字:")
    xx = int(x)
    if (xx > ran):
        print("Too large!\nThe origin figure is")
        print(ran)
    elif (xx < ran):
        print("Too small!\nThe origin figure is")
        print(ran)
    else:
        print("Right!")


# 2、编写代码：利用 while 循环判断来制作一个猜数字的小游戏
# 问题描述：程序运行时，系统在指定范围内生成一个随机数字，然后用户
# 进行猜测，并根据用户输入进行必要的提示（right, too large, too small），
# 如果猜对则提前结束程序，如果次数用完仍没有猜对，提示游戏结束并给出正
# 确答案。
def fun2():
    ran = random.randint(0, 1000)
    while True:
        x = input("请输入猜测的数字:")
        xx = int(x)
        if (xx > ran):
            print("Too large! Please keep guessing!")
            continue
        elif (xx < ran):
            print("Too small! Please keep guessing!")
            continue
        else:
            print("You're right!")
            break


# 3、有 1、2、3、4 个数字，能组成多少个互不相同且无重复数字的三位
# 数？都是多少？
def fun3():
    sum = 0
    for x in range(1, 5):
        for y in range(1, 5):
            for z in range(1, 5):
                if (x != y) and (x != z) and (y != z):
                    print(x * 100 + y * 10 + z)
                    sum += 1
    print(sum)


# 4、一个数如果恰好等于它的因子之和，这个数就称为"完数"。例如 6=1＋2＋3.编程找出 1000 以内的所有完数
def fun4():
    for i in range(0, 1000):
        factor_list = []
        for j in range(0, i):
            if (i % j == 0):
                factor_list.append(j)
        if (i == sum(factor_list)):
            print(f"{i} = {'+'.join(map(str,factor_list))}")


# 5、编写程序，生成一个包含 50 个随机整数的列表，然后删除其中所有奇
# 数（提示：从后向前删除）
def fun5():
    list1 = []
    for i in range(0, 50):
        list1.append(random.randint(0, 99999))
    for j in range(len(list1) - 1, -1, -1):
        if (list1[j] % 2 != 0):
            del list1[j]
    print(list1)


# 6、编写程序，生成一个包含 20 个随机整数的列表，然后对其中偶数下标
# 的元素进行降序排列，奇数下标的元素不变。
def fun6():
    a = []
    for i in range(0, 20):
        a.append(random.randint(0, 99999))
    print(a)
    for m in range(0, 20, 2):
        for n in range(0, 20, 2):
            if (a[m] > a[n]):
                a[m], a[n] = a[n], a[m]
    print(a)


# 7、编写函数用来计算斐波那契数列中小于参数 n 的所有值。
def fun71(n):
    if (n <= 1):
        return n
    else:
        return fun71(n - 1) + fun71(n - 2)


def fun72(n):
    for i in range(0, n):
        print(fun71(i))


# 8、利用列表实现筛选法求素数
# 问题描述：编写程序，输入一个大于 2 的自然数，然后输出小于该数字的所有素数组成的列表。
def fun8(n):
    a = [1 for i in range(n)]
    for i in range(2, n):
        if (a[i]):
            for j in range(i * i, n, i):
                a[j] = 0
    for m in range(2, n):
        if (a[m]):
            print(m)


# 9、编写函数：判断回文，也就是正读反读都一样的字符串
#  例如：abcba”
def fun9(str):
    str1 = str[::-1]
    if str == str1:
        print("是回文")
    else:
        print("不是回文")


# 10、编写函数：随机产生包含 n 个整数的列表，返回一个元组，其中第一个元素为所有参数的平均值，其他元素为所有参数中大于平均值的整数。
#  例如： 随机产生长度为 3 的列表[2, 1, 3]，输出为（2, 0, 3）


def fun10(n):
    alist = []
    blist = []
    for i in range(0, n):
        alist.append(random.randint(0, 10))
    x = sum(alist) / len(alist)
    blist.append(x)
    for j in range(0, n):
        if (alist[j] > x):
            blist.append(alist[j])
    clist = tuple(blist)
    print(clist)


# 11、编写函数： 一年 365 天， 每周工作 5 天，休息 2 天，休息日水平下降 0.01
# 工作日要努力到什么程度一年后的水平才与每天努力 1%所取得的效果（即 37.78 倍）一样呢？


def fun11():
    power = 1.0
    for i in range(365):
        if i % 7 in [0, 6]:
            power = power * (1 - 0.01)
    return power


# while (fun11() < 37.78):
#     x += 0.01
# print("每天努力的参数是：{:.3f}".format(x))


# 12、查找两个字符串首尾交叉的最大子串长度，连接两个字符串，首尾交叉部分只保留一份。例如，1234 和 2347 连接为 12347
# 要求：程序中使用 lambda 表达式以及函数
def fun12(str1, str2):
    length1 = len(str1)
    length = min(length1, len(str2))
    k = max(range(0, length + 1),
            key=lambda i: i if str1[length1 - i:] == str2[:i] else False)
    return (k, str1 + str2[k:])  # k为重复字符的个数（两个字符串首尾交叉的最大子串长度）


# str1 = '1234'
# str2 = '2347'
# print(fun12(str1, str2))


# 13、列表推导式与字典的应用
# （1）.问题描述：编写程序，先生成包含 1000 个随机字符的字符串，然后统计每个字符出现的次数
# （2）.问题描述：编写一个程序，接受逗号分隔的单词序列作为输入，按字母顺序排序后按逗号分隔的序列打印单词。
# 假设向程序提供以下输入:without,hello,bag,world    则输出为:bag,hello,without,world
def fun13_1():
    str1 = ""
    alist = [0 for i in range(0, 128)]
    for i in range(0, 1000):
        str1 = str1 + chr(random.randint(21, 127))
    print(str1)
    for j in range(0, 1000):
        alist[ord(str1[j])] = alist[ord(str1[j])] + 1
    for k in range(0, 128):
        print(chr(k), ": ", alist[k])


def fun13_2():
    item = [x for x in input("请输入：").split(',')]
    item.sort()
    print(', '.join(item))


# 14、集合的应用
# （1）.问题描述：编写程序，输入两个集合 setA 与 setB，分别输出它们两个交集的交、差、并。
# （2）.编写一个程序，接受一系列空格分隔的单词作为输入，在删除所有重复的单词并按字母数字排序后打印这些单词。


def fun14_1():
    setA = eval(input('请输入一个集合：'))
    setB = eval(input('再输入一个集合：'))
    print('交集：', setA & setB)
    print('并集：', setA | setB)
    print('差集：', setA - setB)


def fun14_2():
    str1 = input("请输入一段以空格为分割的单词字符串：\n")
    list1 = str1.split(' ')
    list2 = set(list1)
    print(sorted(list2))


# 15、字符串与列表推导式的应用
# 问题描述： 编写程序，生成含有 n 个元素的嵌套列表，即列表的每个元素仍是列表，
# 要求列表中的元素是长度不超过 m 的数字或字符组成的字符串，并按照字符串长度降序输出结果。


def getlen(elem):
    return len(elem)


def create_list(n, m):
    x = string.ascii_letters + string.digits
    ll = [
        ''.join([random.choice(x) for _ in range(random.randint(1, m + 1))])
        for _ in range(n)
    ]
    # print(ll)
    ll.sort(key=getlen, reverse=True)
    print(ll)


# 16、列表与切片的应用
# 问题描述：编写程序，生成一个整型列表，输出包含原列表中所有元素的新列表、
# 包含原列表中所有元素的逆序列表，以及输出具有偶数位置的元素列表。


def fun16():
    intlist = [i for i in range(0, 10)]
    print(intlist)
    print(intlist[::-1])
    print(intlist[::2])


# 17、元组的应用
# 问题描述：编写程序，利用生成器推导式生成包含 n 个整数元素的元组，
# 每个元素值不大于 m，并过滤掉偶数整数，并输出。


def fun17(n, m):
    TP = [random.randint(0, m) for i in range(0, n)]
    for i in range(0, len(TP), -1):
        if TP[i] % 2 == 0:
            del TP[i]
    tuple(TP)
    print(TP)


# 18、字典的应用
# 问题描述：编写程序，输入任意长度的字符串，统计每个单词出现的次数并存储到字典进行输出。
# 例如：输入：“I love China”，输出：I：1 love: 1 China: 1
def fun18():
    word = input("请输入语句：").split(' ')
    values = [0 for i in range(0, len(word))]
    Dic = dict(zip(word, values))
    for i in range(0, len(word)):
        Dic[word[i]] += 1
    print(Dic)


# 19、正则表达式的应用
# （1）.用户输入一段英文，然后输出这段英文中所有长度为 3 个字母的单词。
# （提示：可以调用 findall 函数，也可以先调用 split 函数将字符串进行分隔，再搜索长度为 3 的单词。）
def fun19():
    sentence = input("Please enter text:")
    pattern = r'\b[a-zA-Z]{3}\b'
    match = re.findall(pattern, sentence)
    print(match)


# 20、将字符串："a:1*a1:2*a2:3*a3:4"
# 处理成 python 字典：{'a':'1', 'a1':'2', 'a2':'3','a3':'4' }
def fun20():
    str1 = "a:1*a1:2*a2:3*a3:4"
    pattern_keys = r'\w+:'
    pattern_values = r':\d'
    keys = ''.join(re.findall(pattern_keys, str1))
    keys = re.findall(r'\w+', keys)
    values = ''.join(re.findall(pattern_values, str1))
    values = re.findall(r'\d+', values)
    Dic = dict(zip(keys, values))
    print(Dic)


# 21、用 Python 实现一个二分查找的函数
def fun21(aim):
    values = [1, 425, 2, 534, 3, 25, 665, 47, 2, 24]
    low = 0
    high = len(values) - 1
    values.sort()
    while (low <= high):
        mid = (low + high) // 2
        if (values[mid] == aim):
            return mid
        elif (values[mid] > aim):
            high = mid - 1
        else:
            low = mid + 1


# 22、一个列表中保存了一些整数，请输出列表中重复的数字，以及重复的次数
def fun22():
    value = [1, 1, 2, 4, 8, 8, 3, 32, 5, 2, 5, 7, 4]
    rep = [0 for i in range(0, max(value) + 1)]
    for i in range(0, len(value)):
        rep[value[i]] += 1
    for i in range(0, len(rep)):
        if (rep[i] != 0):
            print(i, ": ", rep[i])


# 23、输入一个不多于 5 位的正整数，请输出它的位数，以及逆序输出各位数字。
def fun23():
    x = input()
    print("位数为", len(x))
    print(x[::-1])


# 24、随机产生一个 10 以内的正整数，由用户去猜这个数字，
# 程序根据用户猜测的数字给出不同的提示，如果用户猜 3 次不能正确，退出程序.
def fun24():
    x = random.randint(1, 11)
    for i in range(3, 0, -1):
        st = eval(input("请输入数字："))
        if (st == x):
            print("恭喜您猜对了！您一共猜了", 3 - i + 1, "次！")
            return
        elif (st > x):
            print("猜大了！您还有", i - 1, "次机会！")
        else:
            print("猜小了！您还有", i - 1, "次机会！")
    print("真可惜！答案是", x)
