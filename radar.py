import serial
import time
import pygame
from math import sin, cos, radians, sqrt

arduino = serial.Serial(port='COM3',   baudrate=9600, timeout=.2)
screen = pygame.display.set_mode((400, 400))
run = True
objects = {}

def distance(p1, p2):
    return sqrt((p2[0]-p1[0])**2 + (p2[1]-p1[1])**2)

def write_read():
    arduino.write(bytes('a',   'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return   data


while run:
    value = write_read()
    try:
        value = value.decode("utf-8").strip().split(' ')
        value[0], value[1] = int(value[0]), float(value[1])
    except:
        print('error decoding: ', end='')
        print(value)
    print(value)
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
            
            
    pygame.draw.rect(screen, (10, 10, 10), (0, 0, 400, 400))
    pygame.draw.circle(screen, (50, 120, 50), (200, 200), 150)
    try:
        if distance((200 + cos(radians(value[0]))*round((150* value[1]/50)), 200 + sin(radians(value[0]))*round((150* value[1]/50))), (200, 200)) < 150:
            pygame.draw.line(screen, (10, 10, 10), (200, 200), (200 + cos(radians(value[0]))*round((150* value[1]/50)), 200 + sin(radians(value[0]))*round((150* value[1]/50))), 1)
            objects[value[0]] = [[200 + cos(radians(value[0]-5))*round((150* value[1]/50)), 200 + sin(radians(value[0]-5))*round((150* value[1]/50))], [200 + cos(radians(value[0]+5))*round((150* value[1]/50)), 200 + sin(radians(value[0]+5))*round((150* value[1]/50))]]
        else:
            objects[value[0]] = 0
    except:
        pass
    
    for i in objects:
        if objects[i] == 0:
            continue
        pygame.draw.line(screen, (40, 40, 40), objects[i][0], objects[i][1], 2)
        if i-10 in objects:
            if objects[i-10] == 0:
                continue
            pygame.draw.line(screen, (40, 40, 40), objects[i-10][1], objects[i][0], 2)
            
            
    pygame.display.update()
pygame.quit
