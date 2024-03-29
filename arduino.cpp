/* 
  bardzo work in progress. Na razie nie robi nic. Możę w domu coś dodam.
*/
enum LIGHT_COLOR {RED, ORANGE, GREEN};

struct Lane {
  int port;
  bool open;
  int time_since_change;
  LIGHT_COLOR light_color;
};

struct Road {
  #define LEFT 0;
  #define RIGHT 1;
  #define FORWARD 2;
  #define PEDESTRIANS 3;

  Lane lane[4];
};
Road road[2];
#define VERTICAL 0;
#define HORIZONTAL 0;

const int time_step = 1000;

void set_open(Lane *lane){
  (*lane).open = true;
  (*lane).time_since_change = 0;
}

LIGHT_COLOR get_light_color_for_lane(Lane lane){
  if(lane.open)
    if(lane.time_since_change <= 2000)
      return ORANGE;
    return GREEN;
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

void loop() { 
  for(int road_index = 0; road_index < 2; road_index++){
    update_all_lanes(&(road[road_index]));
    set_light_color_for_all_lanes(&(road[road_index]));
  }
  delay(time_step);
}
