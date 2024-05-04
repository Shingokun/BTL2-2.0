/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
 class MovingObject;
 class Position;
// class Configuration;
 class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type): type(in_type){}
    virtual ~MapElement();
    virtual ElementType getType() const {return type;}
    virtual int getReqEXP() const =0;
};

class Path : public MapElement {
    public:
    Path(): MapElement(PATH){}
    int getReqEXP() const override{return 0; }
};

class Wall : public MapElement {
    public:
    Wall(): MapElement(WALL){}
    int getReqEXP() const override{return 0; }
};

class FakeWall : public MapElement {
    private:
     int req_exp;
    public:
     FakeWall(int in_req_exp): MapElement(FAKE_WALL), req_exp(in_req_exp){}
     int getReqEXP() const override;
};

class Map {
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
  Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols){}
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};


class Position{
    private:
    int r, c;
    public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);

    int getRow() const {return r; }
    int getCol() const {return c; }
    void setRow(int r) { this->r = r; }
    void setCol(int c) { this->c = c; }

    string str() const;

    bool isEqual(int in_r, int in_c) const;
    

};


class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;


public:
    MovingObject(int index, const Position pos, Map * map, const string & name=""): index(index), pos(pos), map(map), name(name) {}
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const {return pos;}
    virtual void move() = 0;
    virtual string str() const = 0;
   virtual string getName() const;
    virtual int getEXP() const;
};

class Sherlock : public MovingObject /* TODO */
{
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    string rule_char;
    int rule_index;
    

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
    : MovingObject(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(min(init_exp,500)), exp(min(init_exp,900)), rule_index(0)
    {
        rule_char = moving_rule;
    }
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    string getName() const override;  
    int getEXP() const override;
    // ...

};

class Watson : public MovingObject/* TODO */ {
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    string rule_char;
    int rule_index;
    
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
    : MovingObject(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(min(init_exp,500)), exp(min(init_exp,900)), rule_index(0)
    {
        rule_char = moving_rule;
    }
    int getEXP() const override;
      Position getNextPosition() override;
    void move() override;
    string str() const override;
    string getName() const override;  
    
};

class Criminal:public MovingObject /* TODO */ {
private:
    // TODO
    Sherlock* sherlock;
    Watson* watson;

public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson): MovingObject(index, init_pos, map, "Criminal"),sherlock(sherlock),watson(watson)
    {

    }

    string getName() const override;
    Position getNextPosition() override;
    void move() override;
    string str() const override;
    // ...
};

class ArrayMovingObject {
private:
    // TODO
    MovingObject** arr_mv_objs;
    int count = 0;
    int capacity;

public:
    ArrayMovingObject(int capacity): capacity(capacity ){
        arr_mv_objs = new MovingObject*[capacity];
    }

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO

public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
