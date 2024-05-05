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
        if (i<0 || j<0 || i> num_rows || j> num_cols)
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
bool Position::isEqual(int in_r,int in_c) const
{
   return (this->r==in_r && this->c==in_c);
}

const Position Position::npos = Position(-1, -1);

string MovingObject::getName() const
{
    return name;
}



Position Sherlock::getNextPosition() 
{
     if (rule_char.empty()) return Position::npos;
        Position next_pos;
        if(rule_char[rule_index] == 'L'){
            next_pos.setCol(next_pos.getCol()-1);
        }
        else if(rule_char[rule_index] == 'R'){
            next_pos.setCol(next_pos.getCol()+1);
        }
        else if(rule_char[rule_index] == 'U'){
            next_pos.setRow(next_pos.getRow()-1);
        }
        else if(rule_char[rule_index] == 'D'){
            next_pos.setRow(next_pos.getRow()+1);
        }
        rule_index = (rule_index + 1) % moving_rule.length();
        return next_pos;
}
void Sherlock::move() 
{
      Position next_pos = getNextPosition();
         if (map->isValid(next_pos, this)) {
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
     if (rule_char.empty()) return Position::npos;
        Position next_pos;
        if(rule_char[rule_index] == 'L'){
            next_pos.setCol(next_pos.getCol()-1);
        }
        else if(rule_char[rule_index] == 'R'){
            next_pos.setCol(next_pos.getCol()+1);
        }
        else if(rule_char[rule_index] == 'U'){
            next_pos.setRow(next_pos.getRow()-1);
        }
        else if(rule_char[rule_index] == 'D'){
            next_pos.setRow(next_pos.getRow()+1);
        }
        rule_index = (rule_index + 1) % moving_rule.length();
        return next_pos;
}
void Watson::move() 
{
      Position next_pos = getNextPosition();
         if (map->isValid(next_pos, this)) {
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
    Position next_pos;
    int max_distance ;
    int dis_sherlock;
    int dis_watson;
    int total_dis;
    dis_sherlock = std::abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                           std::abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = std::abs(pos.getRow() - watson->getCurrentPosition().getRow()) +
                         std::abs(pos.getCol() - watson->getCurrentPosition().getCol());
     total_dis = dis_sherlock + dis_watson;
    max_distance = total_dis;
    //U
    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
    {
      pos =  Position(pos.getRow() - 1, pos.getCol());
    dis_sherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                    abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        next_pos = pos;
    }
    }
    //L
    if (map->isValid(Position(pos.getRow() , pos.getCol()-1), this))
    {
      pos =  Position(pos.getRow() , pos.getCol()-1);
    dis_sherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                 abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        next_pos = pos;
    }
    }
    //D
    if (map->isValid(Position(pos.getRow() +1, pos.getCol()), this))
    {
      pos =  Position(pos.getRow() + 1, pos.getCol());
    dis_sherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                    abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        next_pos = pos;
    }
    }

    //R
    if (map->isValid(Position(pos.getRow() , pos.getCol()+1), this))
    {
      pos =  Position(pos.getRow() , pos.getCol()+1);
    dis_sherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                 abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) ;
    dis_watson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) +
                abs(pos.getCol() - watson->getCurrentPosition().getCol());
    total_dis = dis_sherlock + dis_watson;
    if (total_dis > max_distance) 
    {
        next_pos = pos;
    }
    }

    

    return next_pos;
}
void Criminal::move() 
{
      Position next_pos = getNextPosition();
         if (map->isValid(next_pos, this)) {
            pos = next_pos;
        }
}
ArrayMovingObject::~ArrayMovingObject()
{
    for (int i = 0; i < count; ++i) {
            delete arr_mv_objs[i];
        }
        delete[] arr_mv_objs;
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

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
/////////////////////////////////////////////intint