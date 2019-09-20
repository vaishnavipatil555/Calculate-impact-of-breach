from flask import Flask, render_template, request
import math
app = Flask(__name__)
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
    
def get_protocol_list(tcp, udp, icmp, all):
    if all is True:
        return ['tcp', 'udp', 'icmp']
    res = list()
    if tcp is True:
        res.append('tcp')
    if udp is True:
        res.append('udp')
    if icmp is True:
        res.append('icmp')
    return res

def get_res(protocol_list, VM, al):
    if al:
        return list(set(get_impact('./impact/impact_tcp.txt', VM) + get_impact('./impact/impact_udp.txt', VM) + get_impact('./impact/impact_icmp.txt', VM)))
    res = list()
    if('tcp' in protocol_list):
        res = get_impact('./impact/impact_tcp.txt', VM)
    if('udp' in protocol_list):
        res = res + get_impact('./impact/impact_udp.txt', VM)
    if('icmp' in protocol_list):
        res = res + get_impact('./impact/impact_icmp.txt', VM)
    return list(set(res))

@app.route('/result', methods=['POST'])
def result():
    VM = request.form.get("VM", type = int)
    tcp = request.form.get("TCP", type = bool)
    udp = request.form.get("UDP", type = bool)
    icmp = request.form.get("ICMP", type = bool)
    al = request.form.get("ALL", type = bool)
    
    protocol_list = get_protocol_list(tcp, udp, icmp, al)

    res = get_res(protocol_list, VM, al)
    return render_template('result.html', VM=VM, res=res, protocol_list=protocol_list)

if __name__ == '__main__':
    app.run(debug=True)
