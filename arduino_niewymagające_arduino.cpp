#include<iostream>
using namespace std;

/*
  imagine putting something useful in a preamble
  (c) LetMeUseVimCompany69420  
*/
enum LIGHT_COLOR {RED, ORANGE, GREEN};

struct Lane {
  int port;
  bool open = false;
  int time_since_change = 99999;
  LIGHT_COLOR light_color = RED;
};

struct Road {
  #define LEFT 0
  #define RIGHT 1
  #define FORWARD 2
  #define PEDESTRIANS 3

  Lane lane[4];
};
Road road[2];
#define VERTICAL 0
#define HORIZONTAL 1

const int time_step = 1000;

void set_close(Lane *lane){
  if((*lane).open){
    (*lane).open = false;
    (*lane).time_since_change = 0;
  }
}

void set_open(Lane *lane){
  if(!(*lane).open){
    (*lane).open = true;
    (*lane).time_since_change = 0;
  }
}

LIGHT_COLOR get_light_color_for_lane(Lane lane){
  if(lane.open){
    if(lane.time_since_change <= 1000)
      return ORANGE;
    return GREEN;
  }
  if(lane.time_since_change <= 1000)
    return ORANGE;
  return RED;
}

void set_light_color_for_all_lanes(Road *road){
  for(int lane_index = 0; lane_index < 4; lane_index++){
    (*road).lane[lane_index].light_color = get_light_color_for_lane((*road).lane[lane_index]);
  }
}

void update_all_lanes(Road *road){
  for(int lane_index = 0; lane_index < 4; lane_index++){
    (*road).lane[lane_index].time_since_change += time_step;
  }
}

int t;
int seq[16] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};

void loop() { 
  if(t == 0){
    set_close(&(road[HORIZONTAL].lane[LEFT]));
    set_open(&(road[VERTICAL].lane[FORWARD]));
    if(seq[t]){
      set_close(&(road[VERTICAL].lane[RIGHT]));
      set_close(&(road[HORIZONTAL].lane[RIGHT]));
      set_open(&(road[HORIZONTAL].lane[PEDESTRIANS]));
    }
  }else if(t == 3){
    set_close(&(road[VERTICAL].lane[FORWARD]));
    set_open(&(road[VERTICAL].lane[LEFT]));
    set_open(&(road[VERTICAL].lane[RIGHT]));
    set_open(&(road[HORIZONTAL].lane[RIGHT]));
    set_close(&(road[HORIZONTAL].lane[PEDESTRIANS]));
  }else if(t == 7){
    set_close(&(road[VERTICAL].lane[LEFT]));
    set_open(&(road[HORIZONTAL].lane[FORWARD]));
    if(seq[t]){
      set_close(&(road[VERTICAL].lane[RIGHT]));
      set_close(&(road[HORIZONTAL].lane[RIGHT]));
      set_open(&(road[VERTICAL].lane[PEDESTRIANS]));
    }
  }else if(t == 11){
    set_close(&(road[HORIZONTAL].lane[FORWARD]));
    set_open(&(road[HORIZONTAL].lane[LEFT]));
    set_open(&(road[VERTICAL].lane[RIGHT]));
    set_open(&(road[HORIZONTAL].lane[RIGHT]));
    set_close(&(road[VERTICAL].lane[PEDESTRIANS]));
  }

  for(int road_index = 0; road_index < 2; road_index++){
    update_all_lanes(&(road[road_index]));
    set_light_color_for_all_lanes(&(road[road_index]));
  }
  //delay(time_step);
}

char print_light(Lane lane){
  LIGHT_COLOR color = lane.light_color;
  switch(color){
    case GREEN:
      return 'G';
    case ORANGE:
      return 'O';
    case RED:
      return 'R';
  }
  return 'R';
};

int main(){
  t = 0;
  while(true){
    cin.get();
    loop();
    cout << "  "<< print_light(road[VERTICAL].lane[3]) << "######"<< print_light(road[VERTICAL].lane[3]) << "  \n";
    cout << "  |      |  \n";
    cout << print_light(road[1].lane[3]) << "-+" << print_light(road[0].lane[1]) << print_light(road[0].lane[2]) << print_light(road[0].lane[0]) << "   +-"<<print_light(road[1].lane[3])<<"\n";
    cout << "#        "<< print_light(road[1].lane[1]) << " #\n";
    cout << "#        "<< print_light(road[1].lane[2]) << " #\n";
    cout << "#        "<< print_light(road[1].lane[0]) << " #\n";
    cout << "# "<< print_light(road[1].lane[0]) << "        #\n";
    cout << "# "<< print_light(road[1].lane[2]) << "        #\n";
    cout << "# "<< print_light(road[1].lane[1]) << "        #\n";
    cout << print_light(road[1].lane[3]) << "-+   " << print_light(road[0].lane[0]) << print_light(road[0].lane[2]) << print_light(road[0].lane[1]) << "+-"<<print_light(road[1].lane[3])<<"\n";
    cout << "  |      |  \n";
    cout << "  "<< print_light(road[VERTICAL].lane[3]) << "######"<< print_light(road[VERTICAL].lane[3]) << "  \n";
    cout << endl << endl;
    t++;
    t %= 16;
 }
}
