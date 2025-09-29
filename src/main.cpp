#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>
#include <ctime>
#include <cstdint>

struct Particle {
    sf::CircleShape shape;
    sf::Vector2f vel;
    bool alive = true;
};

float length(const sf::Vector2f& v){ 
    return std::sqrt(v.x*v.x + v.y*v.y); 
}

sf::Vector2f normalize(const sf::Vector2f& v){
    float l = length(v);
    return (l == 0.f) ? sf::Vector2f(0,0) : sf::Vector2f(v.x/l, v.y/l);
}

int main(){
    const unsigned W = 1200, H = 800;
    sf::RenderWindow window(sf::VideoMode({W, H}), "Black Hole Visualization (Realistic)");
    window.setFramerateLimit(60);

    sf::Vector2f bhPos(W/2.f, H/2.f);
    float bhRadius = 80.f;
    sf::CircleShape bh(bhRadius);
    bh.setOrigin(sf::Vector2f(bhRadius, bhRadius));
    bh.setPosition(bhPos);
    bh.setFillColor(sf::Color::Black);

    sf::CircleShape bhGlow(bhRadius * 1.6f);
    bhGlow.setOrigin(sf::Vector2f(bhRadius*1.6f, bhRadius*1.6f));
    bhGlow.setPosition(bhPos);
    bhGlow.setFillColor(sf::Color(50,50,80,150));

    sf::CircleShape photonRing(bhRadius * 1.3f);
    photonRing.setOrigin(sf::Vector2f(bhRadius*1.3f, bhRadius*1.3f));
    photonRing.setPosition(bhPos);
    photonRing.setFillColor(sf::Color::Transparent);
    photonRing.setOutlineThickness(6);
    photonRing.setOutlineColor(sf::Color(255, 200, 100, 120));

    sf::CircleShape disk(bhRadius*2.0f);
    disk.setOrigin(sf::Vector2f(bhRadius*2.0f, bhRadius*2.0f));
    disk.setPosition(bhPos);
    disk.setOutlineThickness(3);
    disk.setOutlineColor(sf::Color(220,150,80,100));
    disk.setFillColor(sf::Color::Transparent);

    std::vector<Particle> particles;
    const int N = 1000;
    particles.reserve(N);
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::uniform_real_distribution<float> rx(0, (float)W), ry(0, (float)H), rv(-50,50);

    for(int i=0;i<N;i++){
        Particle p;
        p.shape = sf::CircleShape(1.5f);
        p.shape.setFillColor(sf::Color::White);
        p.shape.setPosition(sf::Vector2f(rx(rng), ry(rng)));
        p.vel = sf::Vector2f(rv(rng), rv(rng));
        particles.push_back(std::move(p));
    }

    const float G = 6000.0f;
    sf::Clock clock;
    
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        float dt = clock.restart().asSeconds();
        if (dt <= 0) dt = 1.f/60.f;

        for(auto &p : particles){
            if(!p.alive) continue;
            sf::Vector2f pos = p.shape.getPosition();
            sf::Vector2f dir = bhPos - pos;
            float r = length(dir);
            float minR = 10.f;
            float rclamped = std::max(r, minR);

            sf::Vector2f a = normalize(dir) * (G / (rclamped*rclamped));

            sf::Vector2f tangent(-dir.y, dir.x);
            tangent = normalize(tangent);
            float tangential_strength = std::clamp(300.0f / rclamped, 0.0f, 150.0f);
            a += tangent * tangential_strength;

            p.vel += a * dt;
            p.shape.move(p.vel * dt);

            if(r <= bhRadius){
                p.alive = false;
                float side = std::uniform_real_distribution<float>(0,4)(rng);
                float x=0,y=0;
                if(side < 1){ x=0; y=ry(rng); }
                else if(side < 2){ x=(float)W; y=ry(rng); }
                else if(side < 3){ x=rx(rng); y=0; }
                else { x=rx(rng); y=(float)H; }
                p.shape.setPosition(sf::Vector2f(x,y));
                p.vel = sf::Vector2f(rv(rng), rv(rng));
                p.alive = true;
            }
        }

        window.clear(sf::Color(5,5,15));

        window.draw(bhGlow);
        window.draw(disk);
        window.draw(photonRing);

        for(auto &p : particles){
            float spd = length(p.vel);
            float r = length(p.shape.getPosition() - bhPos);

            float t = std::clamp((bhRadius*4.f - r) / (bhRadius*4.f), 0.f, 1.f);
            std::uint8_t R = static_cast<std::uint8_t>(255 * t + 220 * (1-t));
            std::uint8_t Gc = static_cast<std::uint8_t>(180 * (1-t) + 80 * t);
            std::uint8_t B = static_cast<std::uint8_t>(200 * (1-t));
            std::uint8_t A = static_cast<std::uint8_t>(std::min(255.f, 50.f + spd*1.8f));

            p.shape.setFillColor(sf::Color(R, Gc, B, A));
            window.draw(p.shape);
        }

        window.draw(bh);
        window.display();
    }
    return 0;
}
