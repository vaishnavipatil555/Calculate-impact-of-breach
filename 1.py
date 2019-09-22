def get_impact(filename, VM):
    f = open(filename, 'r')
    lines = f.readlines()
    f.close()
    """try:
        f = open(filename, 'r')
        lines = f.readlines()
        f.close()
    except:
        return []"""
    all_lines = list()
    for x in lines:
        all_lines.append(x.strip().split(' '))
    res = list()
    for x in all_lines:
        if int(x[0]) == VM:
            res = x[1:]
            break
    return res

print(get_impact('impact.txt', 1))