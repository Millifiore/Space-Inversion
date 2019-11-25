#include "scene.h"

LevelScene::LevelScene(SDL_Renderer * r,Framebuffer * framebuffer, SpriteCache * sprite_cache, TextCache * text_cache){
    this->framebuffer = framebuffer;
    this->hud = new Hud(sprite_cache,framebuffer,player,text_cache);
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
    hud->player = p;
}

void LevelScene::Process(Clock * clock, KeyboardManager * keyboard, ControllerManager * controllers,  int width, int height){
    if (starting){
        // This is here in case we need to set individual player state based on stuff.

        // below we are creating random stars to populate the level, using different layering.
        for (int i=0; i < 9; i++){
            int random_x = rand() % (width-5) + 10;
            int random_y = rand() % (height-5) + 10;
            stars_l1.push_back(new Bullet(renderer, random_x, random_y, 5, 5, {255, 255, 255, 255}));
        }

        for (int i=0; i < 5; i++){
            int random_x = rand() % (width-5) + 10;
            int random_y = rand() % (height-5) + 10;
            stars_l2.push_back(new Bullet(renderer, random_x, random_y, 5, 5, {255, 255, 255, 255}));
        }
    
        running = true;
        starting = false;
    }

    if (running){
        
        // Managing movement for player
        if (keyboard->KeyIsPressed(SDL_SCANCODE_A) || controllers->GetControllerButtonPressed(0, "LEFT")){
            player->Move("left");
        }
        else if (keyboard->KeyIsPressed(SDL_SCANCODE_D) || controllers->GetControllerButtonPressed(0, "RIGHT")) {
            player->Move("right");
        }
        else{
            player->Move("none");
        }

        if (keyboard->KeyIsPressed(SDL_SCANCODE_SPACE) || controllers->GetControllerButtonPressed(0, "X")) {
            if (player->Attack()){
                controllers->SetControllerRumble(0, 20, 0, .3);
            } 
        }

        if (keyboard->KeyWasPressed(SDL_SCANCODE_R)) {
            for (auto enemy: enemies){
                enemy->Reset();
            }
        }

        // make sure the player can't move outta bounds.
        if (player->d_rect.x < -1){
            player->Move("none");
            player->x_pos += 1;
        }
        else if (player->d_rect.x > width - (player->d_rect.w - 1)){
            player->Move("none");
            player->x_pos -= 1;
        }

        // Process player and enemies.
        player->Process(clock);
        ManageEnemies(clock, controllers, width, height);

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


// This method handles all of the specific interactions between enemies (of different types), and the player, as well
// as that's important for interactions.
void LevelScene::ManageEnemies(Clock * clock, ControllerManager * controllers, int width, int height){
    if (enemy_state == "PHASE_DOWN"){
        countdown += clock->delta_time_s;
    }

    shoot_timer += clock->delta_time_s;

    int random_index = 0;
    if (enemies.size()){
        random_index = rand() % enemies.size();
    }

    enemies_dead = 0;
    for (int i = 0; i < enemies.size();i++){
        /*
        "DYING" state is captured quicker than dead boolean or dead state
        (as enemy plays dying animation before the dead boolean is set),
        allowing the score to be set immediately upon the enemy dying
        */ 
        if (enemies[i]->state == "DYING" || enemies[i]->state == "DEAD"){
            enemies_dead++;
        }
    }

    hud->SetScore(enemies_dead * 200);

    for (int i = 0; i < enemies.size(); i++){
        
        // Process the enemy as soon as it comes up.
        if(!enemies[i]->dead){
            double speed_multiplier = double(enemies_dead)/double((enemies.size()-1))*12;
            enemies[i]->speed = int(speed_multiplier) + enemies[i]->default_speed;
        }

        if (!enemies[i]->dead){
            if (enemy_state == "PHASE_LEFT"){
                enemies[i]->Move("left");
                if (enemies[i]->d_rect.x <= 0){
                    last_state = enemy_state;
                    enemy_state = "PHASE_DOWN";
                } 
            }
            else if (enemy_state == "PHASE_RIGHT"){
                enemies[i]->Move("right");
                if (enemies[i]->d_rect.x >= width - enemies[i]->d_rect.w){
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
        if (!enemies[i]->dead){
            if (shoot_timer >= 2){
                if (i == random_index){
                    enemies[i]->Attack();         
                }
            }
        }

        // check if the enemy collided with any of the players bullets.
        int index = 0;
        if (player->TouchingBullet(&enemies[i]->d_rect)){
            for (auto bullet: player->bullets){
                if (enemies[i]->state != "DYING"){
                    if (bullet->IsTouchingRect(&enemies[i]->d_rect)){
                        bullet->hit = true;
                        player->erased.push_back(index);
                    }
                } 
                index++;  
            }
            enemies[i]->state = "DYING";  
        }

        // check if the player collided with any of the enemy bullets.
        if (enemies[i]->TouchingBullet(&player->d_rect)){
            for (auto bullet: enemies[i]->bullets){
                if (bullet->IsTouchingRect(&player->d_rect)){
                    /*
                        TODO: only use this logic for basic pawn bullets. 
                        differentiate when "projectile" class is created and used
                        instead.
                    */
                    if (!bullet->hit){
                        player->lives -= 1;
                        
                    }
                    bullet->hit = true;
                }
            }
        }

        //check if the player collided with any of the enemies
        if (player->TouchingEnemy(&enemies[i]->d_rect)){
            if (enemies[i]->state != "DYING"){
                //TODO: Replace this with player->Hurt() in the future.
                player->lives -= 1;
                controllers->SetControllerRumble(0, 0, 30, .3);
            }
            enemies[i]->state = "DYING";
        }
        //reset enemies to the top if they go off screen
        if(enemies[i]-> y_pos >= 600){
            enemies[i]->SetPos(enemies[i]->x_pos,0);
        }
        enemies[i]->Process(clock, height);
    }

    if (shoot_timer >= 2){shoot_timer = 0.0;}

    // finally, destroy the enemy ship if it is dead.
    // for ( auto enemy = enemies.begin(); enemy != enemies.end(); ) {
    //     if( (*enemy)->dead ) {
    //         delete * enemy;  
    //         enemy = enemies.erase(enemy);
    //     }
    //     else {
    //         ++enemy;
    //     }
    // }

}


void LevelScene::RenderScene(){

    //Rendering
    framebuffer->SetActiveBuffer("GAME");
    SDL_SetRenderDrawColor(renderer, 9, 21, 61, 255);
    SDL_RenderClear(renderer);

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

    framebuffer->UnsetBuffers();

    hud->Render();
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