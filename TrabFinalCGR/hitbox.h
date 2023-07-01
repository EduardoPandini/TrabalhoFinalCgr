#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
public:
    Hitbox(float x, float y, float width, float height);


    
    // Verificar se há colisão com outra hitbox
    bool checkCollision(const Hitbox& other) const;

    // Atualizar a posição da hitbox
    void update(float x, float y);

    // Obter a posição da hitbox
    float getX() const;
    float getY() const;
    
    // Obter a largura e altura da hitbox
    float getWidth() const;
    float getHeight() const;


private:
    float x;
    float y;
    float width;
    float height;
};

#endif // HITBOX_H
