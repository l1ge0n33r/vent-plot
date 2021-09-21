#pragma once 
#include"includes.h"
#include"room.h"

const double e = 2.71828182845904523536;

Room::Room(double volume, double cp, double d_time, double limit, double pv)
    {
        _volume = volume;
        _cp = cp;
        _d_time = d_time;
        _limit = limit;
        _pv = pv;
        _C = _cp - _pv;
        _a = (_volume / _d_time) * log((_C) / (_limit));
    }

void Room::SetNew(double volume, double cp, double d_time, double limit, double pv) 
{
    _volume = volume;
    _cp = cp;
    _d_time = d_time;
    _limit = limit;
    _pv = pv;
    _C = _cp - _pv;
    _a = (_volume / _d_time) * log((_C) / (_limit));
}

double Room::Power()
    {
    _a = (_volume / _d_time) * log((_C) / (_limit));

        return _a;
    }

double Room::OutDependency(double t)
    {
        double y = _pv + _C * pow(e, (-_a * t / _volume));

        return y;
    }

void Room::CalculatePlot()
    {
        int j = 0;
        double t=0;
        for (int i = 0; i < P_WIDTH; i++)
        {   
            t = (OutDependency((double)i/20) *100);
            j = (int)t;
            _plot[P_HEIGHT-1 - j][i] = 1;
        }
    }

void  Room::DrawPlot(int** plot)
    {


    CalculatePlot();
    for (int i = 0; i < P_HEIGHT; i++)
    {
        for (int j = 0; j < P_WIDTH; j++)
        {
            if (_plot[i][j] == 1)
            {
                plot[i][j] = 1;
            }
            else 
            {
                plot[i][j] = 0;
            }
        }
    }
    }
