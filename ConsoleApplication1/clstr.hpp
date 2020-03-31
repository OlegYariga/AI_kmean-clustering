#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <random>
using namespace cv;
using namespace std;

template<typename T, int cn>

class Group{ Mat_<Vec<T, cn>> *img; Vec<T, cn> �; vector<Vec2i> P;
/*����� � ������������ ����� �����������, ��������� ����� � �����, ������������� ����������� ������*/
public:
	/*����������� ������, ����������� ���������� � �������� ���������*/
    Group(Mat_<Vec<T, cn>>& img, int x, int y){ this->img = &img; this->� = img(x, y); }
	/* ���������� ����� x y � ������ ��������*/
	void addPoint(int x, int y) { P.emplace_back(Vec2i(x, y)); }
	/*������� ��� ����� �������� (����� ��� ����������� �������� ���������)*/
	void resetPoints() { P.clear(); }
	/*����� ����������� ������ � ����� � ������ ������������*/
    void moveCenter(){
		/*��������� ����� ��� �����*/
        Vec<uint64_t , cn> buffer;
		/*�������� �� ���� ������ ��������*/
        for(auto& pt : P)
			/*�������� �� ���� ���������*/
            for(int i = 0; i < cn; i++)
				/*������� ����� � �����*/
                buffer[i] += (*img)(pt[0], pt[1])[i];
        buffer /= static_cast<int>(P.size());
		/*�������� �� ���� ���������*/
        for(int i = 0; i < cn; i++)
			/*��������� ����� ������� ��������*/
            �[i] = saturate_cast<T>(buffer[i]);
    }
	void applyCenter() { for (auto pt : P) (*img)(pt[0], pt[1]) = �; }
	/*�������� ���������� ����� �� ������ ��������*/
    long getDistance(int row, int col){
        long distance = 0;
		/*��������� ���������� �����������*/
        Vec<T, cn>* r = img->template ptr<Vec<T, cn>>(row);
		/*�������� �� ���������*/
        for(int i = 0; i < cn; i++)
            distance += (�[i] - r[col][i]) * (�[i] - r[col][i]);
        return distance;
    }

    const Vec<T, cn>& getCenter() {return �;}
    void setCenter(Vec<T, cn>& pt){� = pt;}
    const vector<Vec2i> getPoints(){return P;}
};
