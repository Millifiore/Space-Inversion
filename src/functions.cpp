#include "functions.h"

void ShowError(char * title, string message, string log, bool show_sdl_error){
        string error_string = "";
        if (show_sdl_error){
            error_string = SDL_GetError();
        }
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, (message + error_string).c_str(), NULL);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, (log + error_string).c_str());
}

vector<string> split(string const & word, char delim){
    vector<string> strings;
    stringstream s(word);
    string w;
    while (getline(s, w, delim)){
        strings.push_back(w);
    }

    return strings;
}

LevelScene * CreateScene(SpriteCache * cache, Player * player, string filepath){
    LevelScene * scene = new LevelScene(cache->renderer);
    ifstream level_file(filepath.c_str());
    string line;
    string obj_name;
    string obj_filepath;
    if (level_file.is_open()){
        while (getline(level_file, line)){

            vector<string> section = split(line, '|');

            if (section[0] == "*"){
                vector<string> subsect = split(section[1], ':');
                obj_name = subsect[0];
                obj_filepath = subsect[1];
            }
            else if (section[0] == "+"){
                vector<string> obj_info_list = split(section[1], ',');
                for (auto obj_info: obj_info_list){
                    vector<string> obj_xywh = split(obj_info, '-');
                    if (obj_xywh.size() < 4){}
                    else{
                        int x = stoi(obj_xywh[0]);
                        int y = stoi(obj_xywh[1]);
                        int w = stoi(obj_xywh[2]);
                        int h = stoi(obj_xywh[3]);

                        if (obj_name == "player"){
                            player->x_pos = x;
                            player->y_pos = y;
                            player->d_rect.w = w;
                            player->d_rect.h = h;

                            scene->AddPlayer(player);
                        }
                        else if (obj_name == "villain1"){
                            scene->AddEnemy(new Enemy(cache, x, y, w, h, obj_filepath, "villain1"));
                        }
                        else if (obj_name == "villain2"){
                            scene->AddEnemy(new Enemy(cache, x, y, w, h, obj_filepath, "villain2"));
                        }
                    }
                }
            }
        }
        level_file.close();
    }
    return scene;
}