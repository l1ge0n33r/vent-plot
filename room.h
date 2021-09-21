#ifndef ROOM_H
#define ROOM_H

#define P_WIDTH 400
#define P_HEIGHT 400

class Room 
{
private:
    double _volume,
        _cp,
        _d_time,
        _limit,
        _pv,
        _C,
        _a;

    int _plot[P_HEIGHT][P_WIDTH] = { 0 };
public:
	Room(double volume, double cp, double d_time, double limit, double pv);
    void SetNew(double volume, double cp, double d_time, double limit, double pv);
	double Power();
    double OutDependency(double t);
	void CalculatePlot();
    void DrawPlot(int **plot);

};

#endif