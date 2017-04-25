#Fox Class

import pygame

class Fox():
    def __init__(self, screen):
        self.screen = screen

        #load ship image and get its rect
        self.image = pygame.image.load('babyFox.png')
        #add to reshape size of image
        self.image = pygame.transform.scale(self.image, (70,70))
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()

        #start each new ship at the center of the screen
        self.rect.center = self.screen_rect.center
        #self.rect.bottom = self.screen_rect.bottom

        self.width_image = 100
        #movement flags
        self.moving_left = False
        self.moving_right = False
        self.moving_up = False
        self.moving_down = False

        #fox speed
        self.fox_speed = 7
        #store a decimal value for the foxs center
        self.centerX = float(self.rect.centerx)
        self.centerY = float(self.rect.centery)

        #fox position
        self.x = self.rect.centerx
        self.y = self.rect.centery


    def update(self, screen):
        #update the foxs position based on the movment flag
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.centerX += self.fox_speed
            
        if self.moving_left and self.rect.left > 0:
            self.centerX -= self.fox_speed
            
        if self.moving_up and self.rect.top > self.screen_rect.top:
            self.centerY -= self.fox_speed
         #everything works excpt donw   
        if self.moving_down and self.rect.bottom <  self.screen_rect.bottom:
            self.centerY += self.fox_speed
            
        #update rect object from self.center
        self.rect.centerx = self.centerX
        self.rect.centery = self.centerY

    def move_screen(self, world_shift_hor, world_shift_vert):
        #update x position
        self.x = self.rect.centerx
        self.y = self.rect.centery
        #move background and keep fox stationary
        #if the player get near the right simple world left -
        if self.rect.centerx >= 600:
            ldiff = self.rect.centerx - 600
            self.rect.centerx = 600
            world_shift_hor -= ldiff
        #if the player gets near the left shift the simple right +
        if self.rect.centerx <= 100:
            rdiff = 100 - self.rect.centerx
            self.rect.centerx = 100
            world_shift_hor += rdiff
        #if player gets near the top shift the simple up +
        if self.rect.centery <= 100:
            tdiff = 100 - self.rect.centery
            self.rect.centery = 100
            world_shift_vert -= tdiff
        #if player gets near the bottom shift simple down -
        if self.rect.centery >= 600:
            bdiff = 600 - self.rect.centery
            self.rect.centery = 600
            world_shift_vert += bdiff
        newShift = [world_shift_hor, world_shift_vert]
        return newShift
        
    def blitme(self):
        self.screen.blit(self.image, self.rect)

    def changeImage(self, screen):
        self.image = pygame.image.load('matueFox.png')
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()

    def new_level(self):
        self.fox_speed+=1 


