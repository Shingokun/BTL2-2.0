#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int FakeWall :: getReqEXP() const 
{
   return req_exp;
}
Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls)
:num_rows(num_rows), num_cols(num_cols)
{
      map = new MapElement**[num_rows];
      
        for (int i = 0; i < num_rows; ++i) {
            map[i] = new MapElement*[num_cols];
            for (int j = 0; j < num_cols; ++j) {
                map[i][j] = new Path();
            }
        }
        // Place Wall objects
        for (int i = 0; i < num_walls; ++i) {
            map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall();
        }
        // Place FakeWall objects
        for (int i = 0; i < num_fake_walls; ++i) {
            int x= array_fake_walls[i].getRow();
            int y= array_fake_walls[i].getCol();

            map[x][y] = new FakeWall((x*275+y*139+89)%900 +1 );
        }
}
Map::~Map()
{
     for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
}
bool Map::isValid(const Position& pos, MovingObject* mv_obj) const {
     int i = pos.getRow();
     int j = pos.getCol();
        if (i<0 || j<0 || i>= num_rows || j>= num_cols)
        {   
            return false;
        }
        if (map[i][j]->getType() == WALL) {
              return false;
        }
        if(map[i][j]->getType() == FAKE_WALL){
            if(mv_obj->getName() =="Watson" )
            {
                return (mv_obj->getEXP() > map[i][j]->getReqEXP());
                

                
            }
        }
        return true; // Placeholder
    }
Position::Position(int r, int c):r(r), c(c){}
Position:: Position(const string & str_pos)
{
    istringstream iss(str_pos);
    char nope;
    iss >>nope>>r>>nope>>c>>nope;
}
string Position::str() const
{
     return "(" + to_string(r) + "," + to_string(c) + ")";
}
bool Position::isEqual(const Position &pos) const
{
    return (r == pos.getRow() && c == pos.getCol());
};
const Position Position::npos = Position(-1, -1);
string MovingObject::getName() const
{
    return name;
}
Position Sherlock::getNextPosition() 
{
     Position next_pos = Sherlock::getCurrentPosition();
     if(rule_index == rule_char.length()) rule_index=0;
        if(rule_char[rule_index] == 'L'){
            next_pos.setCol(pos.getCol()-1);
        }
        else if(rule_char[rule_index] == 'R'){
            next_pos.setCol(pos.getCol()+1);
        }
        else if(rule_char[rule_index] == 'U'){
            next_pos.setRow(pos.getRow()-1);
        }
        else if(rule_char[rule_index] == 'D'){
            next_pos.setRow(pos.getRow()+1);
        }
        rule_index++;
        if (map->isValid(next_pos, this))
        {
        return next_pos;
        }
        
     
        return Position::npos;
}
void Sherlock::move() 
{
      Position next_pos = getNextPosition();
      if (!next_pos.isEqual(Position::npos))
      {
        pos = next_pos;
      }  
}
string Sherlock::str() const
{
    return "Sherlock[index=" + to_string(index) + ";pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) +");moving_rule=" + moving_rule + "]";
}
string Sherlock::getName() const 
{
    return "Sherlock"; 
}
int Sherlock::getEXP() const
{
    return exp;
}
Position Watson::getNextPosition() 
{
     Position next_pos = Watson::getCurrentPosition();
    if(rule_index == rule_char.length()) rule_index=0;
    
        if(rule_char[rule_index] == 'L'){
            next_pos.setCol(pos.getCol()-1);
        }
        else if(rule_char[rule_index] == 'R'){
            next_pos.setCol(pos.getCol()+1);
        }
        else if(rule_char[rule_index] == 'U'){
            next_pos.setRow(pos.getRow()-1);
        }
        else if(rule_char[rule_index] == 'D'){
            next_pos.setRow(pos.getRow()+1);
        }
        rule_index++;
        if (map->isValid(next_pos, this))
        {
        
        return next_pos;
        }
        
     
        return Position::npos;
}
void Watson::move() 
{
      Position next_pos = getNextPosition();
      if (!next_pos.isEqual(Position::npos))
      {
        pos = next_pos;
      }
}
string Watson::str() const
{
    return "Watson[index=" + to_string(index) + ";pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) +");moving_rule=" + moving_rule + "]";
}
string Watson::getName() const 
{
    return "Watson"; 
}
int Watson::getEXP() const
{
    return exp;
}
string Criminal::getName() const
{
    return "Criminal";
}
string Criminal::str() const
{
    return "Criminal[index=" + to_string(index) + ";pos=(" + to_string(pos.getRow()) + "," + to_string(pos.getCol()) +")]";
}
Position Criminal::getNextPosition() 
{
    previousPosition = Criminal::getCurrentPosition();
    Position next_pos ;
    int max_distance =0;
    int dis_sherlock =0 ;
    int dis_watson = 0;
    int total_dis = 0;
   dis_sherlock = std::abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                           std::abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = std::abs(pos.getRow() - watson->getCurrentPosition().getRow()) +
                         std::abs(pos.getCol() - watson->getCurrentPosition().getCol());
     total_dis = dis_sherlock + dis_watson;
    max_distance = total_dis;
    //U
    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
    {
      next_pos =  Position(pos.getRow() - 1, pos.getCol());
    dis_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                    abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        return next_pos;
    }
    }
    //L
    else if (map->isValid(Position(pos.getRow() , pos.getCol()-1), this))
    {
      next_pos =  Position(pos.getRow() , pos.getCol()-1);
    dis_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                 abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        return next_pos;
    }
    }
    //D
    if (map->isValid(Position(pos.getRow() +1, pos.getCol()), this))
    {
      next_pos =  Position(pos.getRow() + 1, pos.getCol());
    dis_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                    abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        return next_pos;
    }
    }

    //R
    if (map->isValid(Position(pos.getRow() , pos.getCol()+1), this))
    {
      next_pos =  Position(pos.getRow() , pos.getCol()+1);
    dis_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                 abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        return next_pos;
    }
    }
    
        return Position::npos;
    
}
void Criminal::move() 
{
      Position next_pos = getNextPosition();
        if (!next_pos.isEqual(Position::npos))
    {
        
        pos = next_pos;
        
    }
}
bool ArrayMovingObject::isFull() const
{
    return count == capacity;
}
bool ArrayMovingObject::add(MovingObject * mv_obj)
{
     if (!isFull()) {
            arr_mv_objs[count++] = mv_obj;
            return true;
        }
        return false;
}
string ArrayMovingObject::str() const{
    string result = "ArrayMovingObject[count=" + std::to_string(count) +
                            ";capacity=" + std::to_string(capacity) + ";";
        for (int i = 0; i < count; ++i) {
            result += arr_mv_objs[i]->str();
            if (i < count - 1) {
                result += ";";
            }
        }
        result += "]";
        return result;
}
Configuration ::Configuration(const string &filepath)
{
    ifstream file(filepath);
    string line;
    
    while (getline(file, line)) 
    {
        
        if( line.find("MAP_NUM_ROWS=")==0)
        {
            map_num_rows = stoi(line.substr(13)); 
        }
        else if(line.find("MAP_NUM_COLS=")==0)
        {
            map_num_cols = stoi(line.substr(13));
        }
    
        else if(line.find("MAX_NUM_MOVING_OBJECTS=")==0)
        {
            max_num_moving_objects = stoi(line.substr(23));
        }
        else if(line.find("ARRAY_WALLS=")==0)
        {

            string wall_positions = line.substr(12); 
            wall_positions = wall_positions.substr(1, wall_positions.length() - 2);
            num_walls = 0;
            for (int i = 0; i < wall_positions.length(); ++i) {
            if (wall_positions[i] == ';') {
            num_walls++;
            }
            }
            num_walls++; 
            arr_walls = new Position[num_walls];
            int wall_index = 0;
            int start_pos = 0;
            for (int i = 0; i <= wall_positions.length(); ++i) {
            if (wall_positions[i] == ';' || i == wall_positions.length()) {
            string wall_token = wall_positions.substr(start_pos, i - start_pos);
            int comma_pos = wall_token.find(",");
            int row = stoi(wall_token.substr(1, comma_pos - 1));
            int col = stoi(wall_token.substr(comma_pos + 1, wall_token.length() - comma_pos - 2));
            arr_walls[wall_index++] = Position(row, col);
            start_pos = i + 1;
            }
            }
            
        }
        else if(line.find("ARRAY_FAKE_WALLS=")==0)
        {
            
            string fake_wall_positions = line.substr(17); 
            fake_wall_positions = fake_wall_positions.substr(1, fake_wall_positions.length() - 2);
            num_fake_walls = 0;
            for (int i = 0; i <= fake_wall_positions.length(); ++i) {
            if (fake_wall_positions[i] == ';') {
            num_fake_walls++ ;
            }
            }
            num_fake_walls ++;
            arr_fake_walls = new Position[num_fake_walls];
            int fake_wall_index = 0;
            int start_pos = 0;
            for (int i = 0; i <= fake_wall_positions.length(); ++i) {
            if (fake_wall_positions[i] == ';' || i == fake_wall_positions.length()) {
            string fake_wall_token = fake_wall_positions.substr(start_pos, i - start_pos);
            int comma_pos = fake_wall_token.find(",");
            int row = stoi(fake_wall_token.substr(1, comma_pos - 1));
            int col = stoi(fake_wall_token.substr(comma_pos + 1, fake_wall_token.length() - comma_pos - 2));
            arr_fake_walls[fake_wall_index++] = Position(row, col);
            start_pos = i + 1;
            }
            }
            
            
        }
        else if(line.find("SHERLOCK_MOVING_RULE=")==0)
        {
            sherlock_moving_rule = line.substr(21);
        }
        else if(line.find("SHERLOCK_INIT_POS=")==0)
        {
          string sherlock_position = line.substr(18);
          istringstream iss(sherlock_position);
          char nope;
          int x,y;
          iss >>nope>>x>>nope>>y>>nope;
          sherlock_init_pos = Position(x,y);
        }
        else if(line.find("SHERLOCK_INIT_HP=")==0)
        {
            sherlock_init_hp = stoi(line.substr(17));
        }
        else if(line.find("SHERLOCK_INIT_EXP=")==0)
        {
            sherlock_init_exp = stoi(line.substr(18));
        }
        else if(line.find("WATSON_MOVING_RULE=")==0)
        {
            watson_moving_rule = line.substr(19);
        }
        else if(line.find("WATSON_INIT_POS=")==0)
        {
            string watson_position = line.substr(16);
            istringstream iss(watson_position);
            char nope;
            int x,y;
            iss >>nope>>x>>nope>>y>>nope;
            watson_init_pos = Position(x,y);
        }
        else if(line.find("WATSON_INIT_HP=")==0)
        {
            watson_init_hp = stoi(line.substr(15));
        }
        else if(line.find("WATSON_INIT_EXP=")==0)
        {
            watson_init_exp = stoi(line.substr(16));
        }
        else if(line.find("CRIMINAL_INIT_POS=")==0)
        {
            string criminal_position = line.substr(18);
            istringstream iss(criminal_position);
            char nope;
            int x,y;
            iss >>nope>>x>>nope>>y>>nope;
            criminal_init_pos = Position(x,y);
        }
        else if(line.find("NUM_STEPS=")==0)
        {
            num_steps = stoi(line.substr(10));
        }
    
    }
    
    file.close();
}
string Configuration::str() const
{
  stringstream ss;
  ss << "Configuration["<<endl;
  ss << "MAP_NUM_ROWS=" << map_num_rows << endl;
  ss << "MAP_NUM_COLS=" << map_num_cols << endl;
  ss << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << endl;
  ss << "NUM_WALLS=" << num_walls << endl;
  ss<<"ARRAY_WALLS=[";
  for (int i = 0; i < num_walls; i++)
  {
    if(i == num_walls-1)
    {
        ss<<"("<<arr_walls[i].getRow()<<","<<arr_walls[i].getCol()<<")]"<<endl;
        break;
    }
    ss<<"("<<arr_walls[i].getRow()<<","<<arr_walls[i].getCol()<<");";
  }
  ss<<"NUM_FAKE_WALLS=" << num_fake_walls << endl;
  ss<<"ARRAY_FAKE_WALLS=[";
  for (int i = 0; i < num_fake_walls; i++)
  {
    if(i == num_fake_walls-1)
    {
        ss<<"("<<arr_fake_walls[i].getRow()<<","<<arr_fake_walls[i].getCol()<<")]"<<endl;
        break;
    }
    ss<<"("<<arr_fake_walls[i].getRow()<<","<<arr_fake_walls[i].getCol()<<");";
  }
  ss<<"SHERLOCK_MOVING_RULE="<<sherlock_moving_rule<<endl;
  ss<<"SHERLOCK_INIT_POS=("<<sherlock_init_pos.getRow()<<","<<sherlock_init_pos.getCol()<<")"<<endl;
  ss<<"SHERLOCK_INIT_HP="<<sherlock_init_hp<<endl;
  ss<<"SHERLOCK_INIT_EXP="<<sherlock_init_exp<<endl;
  ss<<"WATSON_MOVING_RULE="<<watson_moving_rule<<endl;
  ss<<"WATSON_INIT_POS=("<<watson_init_pos.getRow()<<","<<watson_init_pos.getCol()<<")"<<endl;
  ss<<"WATSON_INIT_HP="<<watson_init_hp<<endl;
  ss<<"WATSON_INIT_EXP="<<watson_init_exp<<endl;
  ss<<"CRIMINAL_INIT_POS=("<<criminal_init_pos.getRow()<<","<<criminal_init_pos.getCol()<<")"<<endl;
  ss<<"NUM_STEPS="<<num_steps<<endl;
  ss<<"]";
  return ss.str();
}
Robot::Robot(int index, const Position & init_pos, Map * map, RobotType robot_type, string name, Criminal* criminal=nullptr, Sherlock* sherlock=nullptr, Watson* watson=nullptr)
       :MovingObject(index, init_pos, map, name),robot_type(robot_type),criminal(criminal),sherlock(sherlock),watson(watson){}
void Robot::move(){
    int count;
    if(robot_type== RobotType::SW)
    {
       count = 2;
    }else count =1;
    for (int i = 0; i < count; i++) {
		Position nextPosition = getNextPosition();
		if (!nextPosition.isEqual(Position::npos))
			pos = nextPosition;
	}
}
int Robot::getDistance(MovingObject * mv_obj) const
{
    return abs(mv_obj->getNextPosition().getRow() - pos.getRow())+abs(mv_obj->getNextPosition().getCol() - pos.getCol());
}
string Robot::strR(int distance) const 
{
    string RT;
    switch (robot_type) {
            case C:RT = "C"; break;
		case S: RT = "S"; break;
		case W: RT = "W"; break;
		case SW: RT = "SW"; break;
	}

    string result = "Robot[pos=" + pos.str() + ";type="+RT + ";dist=" + ((distance > 0) ? to_string(distance) : "") + ']';
	return result;    
}
Position RobotS::getNextPosition()
{
    Position next_pos;
    int min_distance =100 ;
    int dis_sherlock = getDistanceS() ;
    //U
    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
    {
      pos =  Position(pos.getRow() - 1, pos.getCol());
    dis_sherlock = getDistanceS() ;
    if (dis_sherlock < min_distance) 
    {
        min_distance = dis_sherlock;
        next_pos = pos;
    }
    }
    //R
    if (map->isValid(Position(pos.getRow() , pos.getCol()+1), this))
    {
      pos =  Position(pos.getRow() , pos.getCol()+1);
    dis_sherlock = getDistanceS();
   
    if (dis_sherlock< min_distance) 
    {
        min_distance = dis_sherlock;
        next_pos = pos;
    }
    }
   
    //D
    if (map->isValid(Position(pos.getRow() +1, pos.getCol()), this))
    {
      pos =  Position(pos.getRow() + 1, pos.getCol());
    dis_sherlock = getDistanceS();
    
    if (dis_sherlock < min_distance) 
    {
        min_distance = dis_sherlock;
        next_pos = pos;
    }
    }
     //L
    if (map->isValid(Position(pos.getRow() , pos.getCol()-1), this))
    {
      pos =  Position(pos.getRow() , pos.getCol()-1);
    dis_sherlock = getDistanceS();
   
   
    if (dis_sherlock< min_distance) 
    {
        min_distance = dis_sherlock;
        next_pos = pos;
    }
    }
    if (next_pos.isEqual(Position::npos)){
            return Position::npos;
    }
    return next_pos;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
/////////////////////////////////////////////intint