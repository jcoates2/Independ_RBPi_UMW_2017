#Wolf Class

import pygame
import math

class Wolf():
    def __init__(self,screen):
        self.screen = screen

        #load ship image and get its rect
        self.image = pygame.image.load('wolf.png')
        #add to reshape size of image
        self.image = pygame.transform.scale(self.image, (70,70))
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()

        #start each new ship at the center of the screen
        self.rect.bottom = self.screen_rect.bottom

        self.width_image = 100
        #movement flags
        self.moving_left = False
        self.moving_right = False
        self.moving_up = False
        self.moving_down = False

        #fox speed
        self.wolf_speed = 6
        #store a decimal value for the wolf center
        self.centerX = float(self.rect.centerx)
        self.centerY = float(self.rect.centery)

        #fox position
        self.x = self.rect.centerx
        self.y = self.rect.centery

    def update(self, screen, fox_avatar):
        
        #update the foxs position based on the movment flag
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.centerX += self.wolf_speed
            
        if self.moving_left and self.rect.left > 0:
            self.centerX -= self.wolf_speed
            
        if self.moving_up and self.rect.top > self.screen_rect.top:
            self.centerY -= self.wolf_speed
         #everything works excpt donw   
        if self.moving_down and self.rect.bottom <  self.screen_rect.bottom:
            self.centerY += self.wolf_speed

        #find difference to make it follow the player
        self.x_diff = fox_avatar.centerX - self.centerX
        self.y_diff = fox_avatar.centerY - self.centerY
        
        self.angle = float(math.atan2(self.x_diff, self.y_diff))
        self.centerX += self.wolf_speed * math.sin(self.angle)
        self.centerY += self.wolf_speed * math.cos(self.angle)
            
        #update rect object from self.center
        self.rect.centerx = self.centerX
        self.rect.centery = self.centerY  
        
        
    def new_level(self):
        self.wolf_speed+=1
        
    def blitme(self):
        self.screen.blit(self.image, self.rect)
