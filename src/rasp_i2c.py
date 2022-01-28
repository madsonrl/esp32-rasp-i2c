import smbus
import time
import struct

bus = smbus.SMBus(1)
address = 0x04

def get_data(): 
    return bus.read_i2c_block_data(address, 0)
    
def get_float(data_bytes,index):
    bytes = data_bytes[4*index:4*index+4]
    aux = bytearray(bytes)
    
    data_float=struct.unpack('<f',aux)[0]
    return data_float
    
while True:
     try:
         data = get_data()
         
         temp =  round(get_float(data,0),2)
         Corrente =  round(get_float(data,1),2)
         #ar = round(get_float(data,2),2)
         #umi = round(get_float(data,3),2)
         
         print("Temp: "+str(temp))
         print("Corrente: "+str(Corrente))
         #print("Ar: "+str(ar))
         #print("Umi: "+str(umi))
         
         print(" ")
     except:
        continue
time.sleep(1)
