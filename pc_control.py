import serial
from time import sleep
import sys

COM_PORT = 'COM82'
BAUD_RATES = 9600
ser = serial.Serial(COM_PORT, BAUD_RATES)


def get_device_feedback(ser):
    count = 1
    while count <= 10:
        if ser.in_waiting:
            mcu_feedback = ser.readline().decode()
            print('控制板回應：', mcu_feedback)
            return mcu_feedback
        sleep(0.5)
        count += 1
    print('Timeout!! 控制板無回應')


def quit_process(ser):
    ser.close()
    print('中斷serial連線並結束程式')
    sys.exit()


if __name__ == '__main__':
    try:
        while True:
            choice = input('按R右轉、按L左轉、按G取得目前角度、按Q關閉程式\n').lower()

            if choice == 'r':
                print('傳送右轉指令')
                ser.write(b'right\n')
                get_device_feedback(ser)
            elif choice == 'l':
                print('傳送左轉指令')
                ser.write(b'left\n')
                get_device_feedback(ser)
            elif choice == 'q':
                quit_process(ser)
            elif choice == 'g':
                print('正在取得目前角度...')
                ser.write(b'get\n')
                val = get_device_feedback(ser)
                # print('目前角度:', val)
            else:
                print('Error! 指令錯誤')
    except KeyboardInterrupt:
        quit_process(ser)
