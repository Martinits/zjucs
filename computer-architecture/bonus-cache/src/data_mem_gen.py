f=open("./data_mem.hex", 'w')
addr=[0x00000004, 0x00000084]
data=["00000008", ""]
for i in range(0, 0x00000100, 4):
    # if addr.count(i) == 1:
    #     f.write(data[addr.index(i)])
    # else:
    f.write("%08x"%(i))
    if i != 0x00000100-4:
        f.write('\n')