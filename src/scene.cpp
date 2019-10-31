#include "scene.h"

LevelScene::LevelScene(SDL_Renderer * r){
    starting = true;
    running = false;
    finished = false;
    renderer = r;
}

void LevelScene::AddEnemy(Enemy * enemy){
    enemies.push_back(enemy);
}

void LevelScene::AddPlayer(Player * p){
    player = p;
}

void LevelScene::Process(Clock * clock, const Uint8 * keyboard, int width, int height){
    if (starting){
        // This is here in case we need to set individual player state based on stuff.

        // below we are creating random stars to populate the level, using different layering.
        for (int i=0; i < 9; i++){
            int random_x = rand() % width + 10;
            int random_y = rand() % height + 10;
            stars_l1.push_back(new Bullet(renderer, random_x, random_y, 5, 5, {255, 255, 255, 255}));
        }

        for (int i=0; i < 5; i++){
            int random_x = rand() % 10 + width;
            int random_y = rand() % 10 + height;
            stars_l2.push_back(new Bullet(renderer, random_x, random_y, 5, 5, {255, 255, 255, 255}));
        }
    
        running = true;
        starting = false;
    }

    if (running){
        
        // Managing movement - new
        if (keyboard[SDL_SCANCODE_A]){
            player->Move("left");
        }
        else if (keyboard[SDL_SCANCODE_D]) {
            player->Move("right");
        }
        else{
            player->Move("none");
        }

        if (keyboard[SDL_SCANCODE_SPACE]) {
            player->Attack();
        }

        // Process Player and enemies.
        player->Process(clock);
        ManageEnemies(clock, width, height);

        // Move the stars.
        for (auto star: stars_l1){
            star->y_pos += (3 * 100) * clock->delta_time_s;
            if (star->y_pos >= height){
                star->y_pos = star->y_pos - height;
            }
        }
        for (auto star: stars_l2){
            star->y_pos += (3 * 100) * clock->delta_time_s;
            if (star->y_pos >= height){
                star->y_pos = star->y_pos - height;
            }
        }

    }
}

void LevelScene::ManageEnemies(Clock * clock, int width, int height){
    if (enemy_state == "PHASE_DOWN"){
        countdown += clock->delta_time_s;
    }

    shoot_timer += clock->delta_time_s;

    int random_index = 0;
    if (enemies.size()){
        random_index = rand() % enemies.size();
    }

    for (int i = 0; i < enemies.size(); i++){
        // Process the enemey as soon as it comes up.
        
        if (enemies[i]->state != "DYING"){
            if (enemy_state == "PHASE_LEFT"){
                    enemies[i]->Move("left");
                    if (enemies[i]->x_pos <= 0){
                        last_state = enemy_state;
                        enemy_state = "PHASE_DOWN";
                    } 
            }
            else if (enemy_state == "PHASE_RIGHT"){
                enemies[i]->Move("right");
                if (enemies[i]->x_pos >= width - enemies[i]->d_rect.w){
                    last_state = enemy_state;
                    enemy_state = "PHASE_DOWN";
                }
            }
            if (enemy_state == "PHASE_DOWN"){
                enemies[i]->Move("down");
                if (countdown >= .2){
                    if (last_state == "PHASE_LEFT"){
                        enemy_state = "PHASE_RIGHT";
                        countdown = 0.0;
                    }
                    else{
                        enemy_state = "PHASE_LEFT";
                        countdown = 0.0;
                    }
                }
            } 
        }

        // select a random ship to shoot at the player.
        if (shoot_timer >= 3){
            if (i == random_index){
                if (enemies[i]->state != "DYING"){
                    enemies[i]->Attack();
                }        
            }
        }

        // check if the enemy collided with any of the players bullets.
        if (player->TouchingBullet(&enemies[i]->d_rect)){
            enemies[i]->state = "DYING";
            int index = 0;
            for (auto bullet: player->bullets){
                if (bullet->IsTouchingRect(&enemies[i]->d_rect)){
                    player->erased.push_back(index);
                }
                index++;
            }
        }

        // check if the player collided with any of the enemy bullets.
        if (enemies[i]->TouchingBullet(&player->d_rect)){
            player->lives -= 1;
            int index = 0;
            for (auto bullet: enemies[i]->bullets){
                if (bullet->IsTouchingRect(&player->d_rect)){
                    enemies[i]->erased.push_back(index);
                }
                index++;
            }
        }

        enemies[i]->Process(clock);
    }

    if (shoot_timer >= 3){shoot_timer = 0.0;}

    // finally, destroy the enemy ship if it is dead.
    for ( auto enemy = enemies.begin(); enemy != enemies.end(); ) {
        if( (*enemy)->dead ) {
            delete * enemy;  
            enemy = enemies.erase(enemy);
        }
        else {
            ++enemy;
        }
    }

}


void LevelScene::RenderScene(){
    for (auto star: stars_l1){
        star->Render();
    }
    for (auto enemy: enemies){
        enemy->Render();
    }

    player->Render();

    for (auto star: stars_l2){
        star->Render();
    }
}

LevelScene::~LevelScene(){
    for (int i=0; i < stars_l1.size(); i++){
        delete stars_l1[i];
    }
    for (int i=0; i < stars_l2.size(); i++){
        delete stars_l2[i];
    }
    for (int i=0; i < enemies.size(); i++){
        delete enemies[i];
    }
}