// this file is cpp realization of game.h an elementary game "engine"

#include "game.h"
#include <iostream>
#include <string>

#define WIDTH 900
#define HEIGHT 600

Game::Game() {
    this->init_window();
    this->initPlayer();
    this->initBackground();
    this->initAllArtefact();
    this->initTextBox();
    this->initTextBoxCompleteTask();
    this->initTextBoxStoryline();
    this->initText();
    this->initWizard();
    this->initDialogBox();
}

Game::~Game() {
    delete this->window;
    delete this->main_hero;
    delete this->artefact;
    delete this->artefact1;
}


void Game::render() {
    //clear old frame
    //render objects
    //display frame in window
    
    this->window->setView(hero_view);
    this->window->clear();
    this->renderBackground();
    this->renderHero();
    this->renderWizard();
    this->renderText();
    if(this->isStorylineBoxVisible) {
        this->renderTextBoxStoryline();
    }
    if(this->isDialogBoxVisible) {
        this->renderDialogBox();
    }
    if(!artefact->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact);
    }
    if(!artefact1->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact1);
    }
    if(!artefact2->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact2);
    }
    if(!artefact3->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact3);
    }
    if(!artefact4->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact4);
    }
    if(!artefact5->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact5);
    }
    if(!artefact6->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact6);
    }
    if(!artefact7->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact7);
    }
    if(!artefact8->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact8);
    }
    if(!artefact9->isDestroyedFunc()) {
        this->renderOneArtefact(*artefact9);
    }
    this->updateView(main_hero->getHeroPositionX(), main_hero->getHeroPositionY());
    if(this->isTaskBoxVisible) {
        this->renderTextBox();
    }
    if(this->isCompleteTaskBoxVisible) {
        this->renderTextBoxCompleteTask();
    }
    this->window->display();
}


void Game::init_window() {
    this->videoMode.height = HEIGHT;
    this->videoMode.width = WIDTH;
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(144);
    this->initView();

}
void Game::initView() {
    hero_view.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
}

void Game::updateView(float x, float y) {
    sf::Vector2f position;
    if(x + 10  > WIDTH / 2) {
        position.x = x + 10;
    }
    else {
        position.x = (WIDTH / 2);
    }
    position.y = y-80;
    hero_view.setCenter(position);
    this->moveText(position);
    this->moveTextBox(position);
    this->moveTextBoxCompleteTask(position);
}

const bool Game::isRunning() {
    return this->window->isOpen();
}

void Game::update() {
      while (this->window->pollEvent(this->event))
        {
            if (this->event.type == sf::Event::Closed)
                window->close();
        }
      this->updateHero();
      this->showTask();
      this->closeTask();
      this->updateWizardAnim();
      this->updateTextBoxStoryline();
      this->updateDialogBox();
}

void Game::updateHero() {
    this->main_hero->update();
}

void Game::initPlayer() {
    this->main_hero = new Hero();
    this->counter_hero = 0;
}

void Game::renderHero() {
    this->main_hero->render(*window);
}

void Game::initBackground() {
    if(!this->background_texture1.loadFromFile("/home/crocus/game_project/game_sprites/maps/cyberpunk-street-files/PNG/cyberpunk-street1.png")) {
        std::cout << "ERROR! COULDN'T LOAD A BACKGROUND" << std::endl;
    }
    else {
        this->background_sprite1.setTexture(background_texture1);
        this->background_sprite1.setScale(WIDTH*10/background_sprite1.getLocalBounds().width, HEIGHT/background_sprite1.getLocalBounds().height);
    }
}

void Game::renderBackground() {
    window->draw(background_sprite1);
}

void Game::initAllArtefact() {
    artefact = new Artefact(1100, main_hero->getHeroPositionY()+500, "Waffles", 5);
    artefact1 = new Artefact(1700, main_hero->getHeroPositionY()+500, "Shrimp", 5);
    artefact2 = new Artefact(2300, main_hero->getHeroPositionY()+500, "Tomato", 5);
    artefact3 = new Artefact(2700, main_hero->getHeroPositionY()+500, "Sashimi", 5);
    artefact4 = new Artefact(3100, main_hero->getHeroPositionY()+500, "Sardines", 5);
    artefact5 = new Artefact(3500, main_hero->getHeroPositionY()+500, "Pretzel", 5);
    artefact6 = new Artefact(3900, main_hero->getHeroPositionY()+500, "Pickle", 5);
    artefact7 = new Artefact(4500, main_hero->getHeroPositionY()+500, "Peach", 5);
    artefact8 = new Artefact(4900, main_hero->getHeroPositionY()+500, "Onion", 5);
    artefact9 = new Artefact(5500, main_hero->getHeroPositionY()+500, "Olive", 5);
}

void Game::renderOneArtefact(Artefact &artefact_num) {
    artefact_num.render(*window);
    this->collisionHeroWithArtefact(artefact_num);
}
void Game::collisionHeroWithArtefact(Artefact &artefact_num) {
    if(artefact_num.getArtefactPositionX() - main_hero->getHeroPositionX() < 120) { 
        artefact_num.destroyArtefact();
        this->updateCounter();
    }
}

void Game::initTextBox() {
    isTaskBoxVisible = false;
    if(!this->textbox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/robot_border_10_artefacts.png")) {
        std::cout << "ERROR! COULDN'T LOAD A BACKGROUND" << std::endl;
    }
    else {
        this->textbox_sprite.setTexture(textbox_texture);
        this->textbox_sprite.setScale(0.8f, 0.8f);
    
    }
}
void Game::renderTextBox() {
    window->draw(textbox_sprite);
}

void Game::updateCounter() {
    this->counter_hero += 1;
    this->updateText(counter_hero);
    this->updateTextBox();
}

void Game::initText() {
    if(!font.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/PressStart2P-Regular.ttf")) {
        std::cout << "COUDLNT NOT LOAD A FONT!" << std::endl;
    }
    counter_text.setFont(font);
    counter_text.setCharacterSize(15);

    std::string counter_string = std::to_string (counter_hero);
    counter_text.setString("artefacts: " + counter_string);
    
}
void Game::renderText() {
    window->draw(counter_text);
}
void Game::updateText(int new_count) {
    std::string counter_string = std::to_string (new_count);
    counter_text.setString("artefacts: " + counter_string);
}
void Game::moveText(sf::Vector2f position) {
    position.x -= 440;
    position.y -= 290;
    counter_text.setPosition(position);
}
void Game::showTask() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
        isTaskBoxVisible = true;
    }
}
void Game::closeTask() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        isTaskBoxVisible = false;
        isCompleteTaskBoxVisible = false;
    }
}
void Game::moveTextBox(sf::Vector2f position) {
    position.x -= 200;
    position.y -= 200;
    textbox_sprite.setPosition(position);

}
void Game::initTextBoxCompleteTask() {
    isCompleteTaskBoxVisible = false;
    if(!this->complete_task_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/completed_task.png")) {
        std::cout << "ERROR! COULDN'T LOAD A COMPLETE TASK TEXTURE" << std::endl;
    }
    else {
        this->complete_task_sprite.setTexture(complete_task_texture);
        this->complete_task_sprite.setScale(0.5f, 0.5f);
    
    }
}
void Game::renderTextBoxCompleteTask() {
    window->draw(complete_task_sprite);
}
void Game::moveTextBoxCompleteTask(sf::Vector2f position) {
    position.x -= 200;
    position.y -= 200;
    complete_task_sprite.setPosition(position);

}

void Game::updateTextBox() {
    if(counter_hero == 10) {
        this->textbox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/robot_border_gohome.png");
        this->textbox_sprite.setTexture(textbox_texture);
        isCompleteTaskBoxVisible = true;
    }
}
void Game::initTextBoxStoryline() {
    isStorylineBoxVisible = false;
    if(!this->storylinebox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/storyline_border_school.png")) {
        std::cout << "ERROR! COULDN'T LOAD A COMPLETE TASK TEXTURE" << std::endl;
    }
    else {
        this->storylinebox_sprite.setTexture(storylinebox_texture);
        this->storylinebox_sprite.setPosition(main_hero->getHeroPositionX()+300, main_hero->getHeroPositionY() + 100);
        this->storylinebox_sprite.setScale(0.5f, 0.5f);
    
    }
}
void Game::updateTextBoxStoryline() {
    if(main_hero->getHeroPositionX() >= 300 && main_hero->getHeroPositionX()<= 310) {
        isStorylineBoxVisible = true;
    }
    else if(main_hero->getHeroPositionX() >= 400 && main_hero->getHeroPositionX()<= 410) {
        storylinebox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/storyline_border_task.png");
        storylinebox_sprite.setTexture(storylinebox_texture);
        isStorylineBoxVisible = true;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        isStorylineBoxVisible = false;
    }
}
void Game::renderTextBoxStoryline() {
    window->draw(storylinebox_sprite);
}

void Game::initDialogBox() {
    isDialogBoxVisible = false;
    counterOfDialogBox = 1;
    if(!this->dialogbox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/dialog_box_choosen_one.png")) {
        std::cout << "ERROR! COULDN'T LOAD A COMPLETE TASK TEXTURE" << std::endl;
    }
    else {
        this->dialogbox_sprite.setTexture(dialogbox_texture);
        this->dialogbox_sprite.setPosition(wizard1_sprite.getPosition().x+50,wizard1_sprite.getPosition().y+100);
        this->dialogbox_sprite.setScale(0.5f, 0.5f);
    
    }
}
void Game::renderDialogBox() {
    window->draw(dialogbox_sprite);
}
void Game::updateDialogBox() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        counterOfDialogBox += 1;
    }
    if(wizard1_sprite.getPosition().x - main_hero->getHeroPositionX() < 100 && counterOfDialogBox == 1) {
        isDialogBoxVisible = true;
    }
    else if(counterOfDialogBox <= 20) {
        isDialogBoxVisible = false;
    }
    else if(wizard1_sprite.getPosition().x - main_hero->getHeroPositionX() < 100 && counterOfDialogBox >= 21 && counterOfDialogBox <= 31) {
        isDialogBoxVisible = true;
        this->dialogbox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/dialog_box_but_why.png");
        this->dialogbox_sprite.setTexture(dialogbox_texture);
        this->dialogbox_sprite.setPosition(main_hero->getHeroPositionX()-170,main_hero->getHeroPositionY()-60);
    }
    else if(counterOfDialogBox >= 33 && counterOfDialogBox <= 41 &&  wizard1_sprite.getPosition().x - main_hero->getHeroPositionX() < 100) {
        isDialogBoxVisible = false;
    }
    else if(counterOfDialogBox >= 41 && counterOfDialogBox <= 61 && wizard1_sprite.getPosition().x - main_hero->getHeroPositionX() < 100) {
        isDialogBoxVisible = true;
        this->dialogbox_texture.loadFromFile("/home/crocus/game_project/game_sprites/another_stuff/dialog_box_lets_see.png");
        this->dialogbox_sprite.setTexture(dialogbox_texture);
        this->dialogbox_sprite.setPosition(wizard1_sprite.getPosition().x+50,wizard1_sprite.getPosition().y+100);
    }
    else if(counterOfDialogBox >= 52 &&  wizard1_sprite.getPosition().x - main_hero->getHeroPositionX() < 100) {
        isDialogBoxVisible = false;
        animNumber = 2;
    }

}



// wizard's function
void Game::initWizard() {
    animNumber = 1;
    this->wizardAnimTimer.restart();
    if(!this->wizard1_texture.loadFromFile("/home/crocus/game_project/game_sprites/main_enemies/EVil Wizard 2/Sprites/Idle.png")) {
        std::cout << "ERROR! COULDN'T LOAD AN EVIL WIZARD SPRITE" << std::endl;
    }
    else {
        this->WizardFrame = sf::IntRect(0, 0, 250, 250);
        this->wizard1_sprite.setTexture(wizard1_texture);
        this->wizard1_sprite.setScale(3.0f, 3.0f);
        this->wizard1_sprite.setTextureRect(this->WizardFrame);
        this->wizard1_sprite.setPosition(7350.f, 80.f);
    }

}
void Game::renderWizard() {
    window->draw(wizard1_sprite);
}
void Game::updateWizardAnim(){
    if(animNumber == 1) {
        if(this->wizardAnimTimer.getElapsedTime().asSeconds() >= 0.1f) {
            this->WizardFrame.top = 0.f;
            this->WizardFrame.left += 250.f;
            if(this->WizardFrame.left >= 1750.f){
                this->WizardFrame.left = 250.f;
            }
            this->wizardAnimTimer.restart();
            this->wizard1_sprite.setTextureRect(this->WizardFrame);
        }
    }
    if(animNumber == 2) {
        if(changeSpriteForAnim == true) {
            this->wizard1_texture.loadFromFile("/home/crocus/game_project/game_sprites/main_enemies/EVil Wizard 2/Sprites/Attack1.png");
            this->WizardFrame = sf::IntRect(0, 0, 250, 250);
            this->wizard1_sprite.setTexture(wizard1_texture);
            this->wizard1_sprite.setScale(3.0f, 3.0f);
            this->wizard1_sprite.setTextureRect(this->WizardFrame);
            this->wizard1_sprite.setPosition(7350.f, 80.f);
            changeSpriteForAnim = false;
        }
        if(this->wizardAnimTimer.getElapsedTime().asSeconds() >= 0.15f) {
            this->WizardFrame.top = 0.f;
            this->WizardFrame.left += 250.f;
            main_hero->animdeath();
            if(this->WizardFrame.left >= 1750.f){
                this->WizardFrame.left = 1750.f;
            }
            this->wizardAnimTimer.restart();
            this->wizard1_sprite.setTextureRect(this->WizardFrame);
            
        }
    }
}
