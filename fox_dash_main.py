#main game
import pygame, time
from fox import Fox
from wolf import Wolf
import sys

def events(fox_avatar):
    #responds to keypresses and mouse events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                fox_avatar.moving_left = True
            elif event.key == pygame.K_RIGHT:
                fox_avatar.moving_right = True
            elif event.key == pygame.K_UP:
                fox_avatar.moving_up = True
            elif event.key == pygame.K_DOWN:
                fox_avatar.moving_down = True
                
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT:
                fox_avatar.moving_left = False
            elif event.key == pygame.K_RIGHT:
                fox_avatar.moving_right = False
            elif event.key == pygame.K_UP:
                fox_avatar.moving_up = False
            elif event.key == pygame.K_DOWN:
                fox_avatar.moving_down = False
        
#detection
def check(fox_avatar, wolf_avatar):
    #print(str(fox_avatar.rect.centerx)+','+str(fox_avatar.rect.centery)+' : '+str(wolf_avatar.rect.centerx)+','+str(wolf_avatar.rect.centery))
    if fox_avatar.rect.centerx == 2-wolf_avatar.rect.centerx or fox_avatar.rect.centery == 4-wolf_avatar.rect.centery:
        return True
    elif fox_avatar.rect.centerx == 3+wolf_avatar.rect.centerx or fox_avatar.rect.centery == 1+wolf_avatar.rect.centery:
        return True
    else:
        return False

        
def run():
    pygame.init()

    size = [700,700]
    screen = pygame.display.set_mode(size)

    simple = pygame.image.load('l_one.png')
    simple_rect = simple.get_rect()

    #create fox and wolf
    fox_avatar = Fox(screen)
    wolf_avatar = Wolf(screen)
    #speed
    clock = pygame.time.Clock()
    #world shift
    world_shift_hor = 0
    world_shift_vert = 0

    pygame.display.set_caption("Fox Dash:Avoid the Wolf for 30 seconds ")
    
    #start and create timer
    startTime = pygame.time.get_ticks()
    seconds = 0

    game_cont = True
    while game_cont == True:
        #show on screen
        screen.blit(simple, simple_rect)
        fox_avatar.blitme()
        wolf_avatar.blitme()
        #check movments
        events(fox_avatar)
        fox_avatar.update(screen)
        wolf_avatar.update(screen,fox_avatar)
        pygame.display.update()
        #collision detection
        if check(fox_avatar, wolf_avatar):
            print('Game over')
            game_cont = False
        #timer 30 seconds
        #restart timer
        if seconds >= 30:
            #startTime = pygame.time.get_ticks()
            #seconds = 0
            print("Round done, You are safe!")
            game_cont = False
        seconds=(pygame.time.get_ticks()-startTime)/1000
        #check to see if there is a collision
        ans = check(fox_avatar, wolf_avatar)
        #speed
        clock.tick(30)
        pygame.display.flip()


run()
pygame.quit()
sys.exit()
