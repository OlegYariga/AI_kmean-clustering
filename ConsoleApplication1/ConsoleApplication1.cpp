// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "clstr.hpp"

int main() {
	// количество кластеров в изображении
	int count_clusters = 1;
    srand(time(NULL));
	// вводим требуемое количество кластеров
	std::cout << "Enter clusters number: ";
	std::cin >> count_clusters;
	// считываем изображение
	auto m = imread("f1.jpg", IMREAD_COLOR);
	// преобразуем вектор к Vec3b (модель RGB)
	Mat_<Vec3b> img(m);
	// вызываем функцию getClusters и передаем ей изображение и кол-во кластеров
	auto clusters = getClusters(img, count_clusters);
	// количество итерраций - 50, оптимальное значение - больше 20
	for (int i = 0; i < 50; ++i) {
		assignPoints(img, clusters);
		// связываем точки с кластером
		for (auto& c : clusters) {
			// перемещаем центр
			c.moveCenter();
		}
	}
	for (auto& c : clusters)
		c.applyCenter();
	// записываем получившееся изображение
	imwrite("f2.jpg", img);
	return 0;
}
