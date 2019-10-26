from flask import Flask, render_template, request
from calc_costt import calc_cost_fun
from operator import itemgetter
import math
import re
app = Flask(__name__, static_folder='./static')
app.config.from_object(__name__)

@app.route('/')
def welcome():
    return render_template('form.html')

def get_impact(filename, VM):
    f = open(filename, 'r')
    lines = f.readlines()
    f.close()
    all_lines = list()
    for x in lines:
        all_lines.append(x.strip().split(' '))
    res = list()
    for x in all_lines:
        if int(x[0]) == VM:
            res = x[1:]
            break
    return res

def get_res(VM, tcp_cost, udp_cost, icmp_cost, no_of_nodes):
    return calc_cost_fun(tcp_cost, udp_cost, icmp_cost, VM, no_of_nodes)
    
def tree_fun(VM, protocol):
    tree = list()
    if protocol == 'udp':
        f = open("./tree/tree_udp.txt")
        i = 0
        lis = f.readlines()
        for x in lis:
            if i == VM:
                tree.append(x.strip("\n"))

            if(x[0] == '\n'):
                i = i + 1
    elif protocol == 'tcp':
        f = open("./tree/tree_tcp.txt")
        i = 0
        lis = f.readlines()
        for x in lis:
            if i == VM:
                tree.append(x.strip("\n"))

            if(x[0] == '\n'):
                i = i + 1
    elif protocol == 'icmp':
        f = open("./tree/tree_icmp.txt") 
        i = 0
        lis = f.readlines()
        for x in lis:
            if i == VM:
                tree.append(x.strip("\n"))

            if(x[0] == '\n'):
                i = i + 1
    return tree


def get_corresponding_vm_to_ip(ip):
    f = open('IPnames.txt', 'r')
    lis = f.readlines()
    i = 0
    for x in lis:
        ipp = x.strip("\n")
        if ipp == ip:
            #print(ipp)
            return i
        i = i + 1
    return -1

def get_corresponding_ip(VM):
    f = open('IPnames.txt', 'r')
    lis = f.readlines()
    return lis[VM]

def legend_fun(tree):
    lis = list()
    for s in tree:
        try:
            res = re.search(r'\d+', s).group()
            if len(res) > 0:
                lis.append([res, get_corresponding_ip(int(res)).strip()])
        except:
            continue
    return lis
    

@app.route('/result', methods=['POST'])
def result():
    ip = request.form.get("VM", type = str)
    VM = get_corresponding_vm_to_ip(ip)
    if(VM == -1):    
        return render_template('error.html', error="Invalid VM IP")

    fp = open("tot_nodes.txt", "r")
    tot_nodes = int(fp.read())
    fp.close()

    tcp_cost = request.form.get("tcp_cost", type = int)
    if(tcp_cost < 0):
        return render_template('error.html', error = "tcp_cost cannot be negative")

    udp_cost = request.form.get("udp_cost", type = int)
    if(udp_cost < 0):
        return render_template('error.html', error = "udp_cost cannot be negative")
    
    icmp_cost = request.form.get("icmp_cost", type = int)
    if(tcp_cost < 0):
        return render_template('error.html', error = "icmp_cost cannot be negative")

    al = request.form.get("ALL", type = bool)

    res = get_res(VM, int(tcp_cost), udp_cost, icmp_cost, tot_nodes)
    

    impacted_nodes = list()
    cost = list()

    ans = list()
    for i in range(0, tot_nodes):
        try:
            if res[i] != 0:
                ans.append([get_corresponding_ip(i), res[i]])
                impacted_nodes.append(i)
                cost.append(res[i])
        except:
            pass
    ans = sorted(ans, key=itemgetter(1), reverse=True)

    tree_udp = tree_fun(VM, 'udp')
    legend_udp = legend_fun(tree_udp)


    tree_tcp = tree_fun(VM, 'tcp')
    legend_tcp = legend_fun(tree_tcp)

    tree_icmp = tree_fun(VM, 'icmp')
    legend_icmp = legend_fun(tree_icmp)

   
    return render_template('result.html', legend_udp=legend_udp, legend_tcp=legend_tcp, legend_icmp=legend_icmp, VM=get_corresponding_ip(VM), ans=ans, tree_udp=tree_udp, tree_tcp=tree_tcp, tree_icmp=tree_icmp, impacted_nodes=impacted_nodes, cost=cost)
    
if __name__ == '__main__':
    app.run(debug=True)
