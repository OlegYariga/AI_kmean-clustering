#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <random>
using namespace cv;
using namespace std;

template<typename T, int cn>

class Group{ Mat_<Vec<T, cn>> *img; Vec<T, cn> С; vector<Vec2i> P;
/*класс с координатами узлов изображения, центровых точек и точек, принадлежащих конкретному центру*/
public:
	/*конструктор класса, изображение передается в качестве параметра*/
    Group(Mat_<Vec<T, cn>>& img, int x, int y){ this->img = &img; this->С = img(x, y); }
	/* добавление точки x y к точкам кластера*/
	void addPoint(int x, int y) { P.emplace_back(Vec2i(x, y)); }
	/*удалить все точки кластера (сброс для дальнейшего просчета дистанции)*/
	void resetPoints() { P.clear(); }
	/*метод перемещения центра в точку с новыми координатами*/
    void moveCenter(){
		/*временный буфер для точек*/
        Vec<uint64_t , cn> buffer;
		/*проходим по всем точкам кластера*/
        for(auto& pt : P)
			/*проходим по всем кластерам*/
            for(int i = 0; i < cn; i++)
				/*заносим точку в буфер*/
                buffer[i] += (*img)(pt[0], pt[1])[i];
        buffer /= static_cast<int>(P.size());
		/*проходим по всем кластерам*/
        for(int i = 0; i < cn; i++)
			/*назначаем точку центром кластера*/
            С[i] = saturate_cast<T>(buffer[i]);
    }
	void applyCenter() { for (auto pt : P) (*img)(pt[0], pt[1]) = С; }
	/*получаем расстояние точек от центра кластера*/
    long getDistance(int row, int col){
        long distance = 0;
		/*построчно перебираем изображение*/
        Vec<T, cn>* r = img->template ptr<Vec<T, cn>>(row);
		/*проходим по кластерам*/
        for(int i = 0; i < cn; i++)
            distance += (С[i] - r[col][i]) * (С[i] - r[col][i]);
        return distance;
    }

    const Vec<T, cn>& getCenter() {return С;}
    void setCenter(Vec<T, cn>& pt){С = pt;}
    const vector<Vec2i> getPoints(){return P;}
};
