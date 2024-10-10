#define MAX_SUBMENUS 10 
typedef struct Menu
{
    char * text; //Title of the menu
    void (*function)(); //Calls to a function if there is no sub menu
    struct Menu * parent; 
    struct Menu * subMenu[MAX_SUBMENUS];
} menu_t, *menu_ptr

*menu_ptr menu = malloc(sizeof(menu_t));
menu_ptr menu_add(menu_ptr parent, char * text, void (*function)())
{
    menu_ptr subMenu = malloc(sizeof(menu_t)); // Creates empty submenu item
    subMenu -> text     = text; //Sets menu title
    subMenu -> function = function;
    subMenu -> parent   = parent;

    int i = 0;
    while(parent -> subMenu[i] != NULL)
    {
        i++;
    }
    parent -> subMenu[i] = subMenu;
    return subMenu;
}

menu_ptr menu = malloc(sizeof(menu_t));

menu_ptr menu_highscore = menu_add(menu, "HIGHSCORE", &show_highscore);
menu_ptr menu_play = menu_add(menu, "Let's play", NULL);

menu_ptr menu_game1 = menu_add(menu_play, "Spill 1", &play_game1);
menu_ptr menu_game2 = menu_add(menu_play, "Spill 2", &play_game2);
menu_ptr menu_game3 = menu_add(menu_play, "Spill 3", $play_game3);

void show_highscore(){}
void play_game1(){}
void play_game2(){}
void play_game3(){}