/*
 * Functions.h
 *
 *  Created on: Apr 14, 2014
 *      Author: blaws
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "Include.h"
using namespace std;

template <typename T>
T max(vector<T> m){
	T max = 0;
	if(m.size()){
		max = m[0];
		for(int i=0,n=m.size(); i<n; ++i){
			if(m[i] > max) max = m[i];
		}
	}
	return max;
}

template <typename T>
T min(vector<T> m){
	T min = 0;
	if(m.size()){
		min = m[0];
		for(int i=0,n=m.size(); i<n; ++i){
			if(m[i] < min) min = m[i];
		}
	}
	return min;
}

template <typename T>
T distance(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2){
	vector<T> hor, vert;

	hor.push_back(fabs(x1-x2));
	hor.push_back(fabs(x1+w1-x2));
	hor.push_back(fabs(x1-x2-w2));
	hor.push_back(fabs(x1+w1-x2-w2));

	vert.push_back(fabs(y1-y2));
	vert.push_back(fabs(y1+h1-y2));
	vert.push_back(fabs(y1-y2-h2));
	vert.push_back(fabs(y1+h1-y2-h2));

	T x = min(hor);
	T y = min(vert);
	return sqrt(x*x + y*y);
}

template <typename T>
bool overlap(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2){
	for(int i=x1; i<=x1+w1; i+=w1){
		for(int j=y1; j<=y1+h1; j+=h1){
			if(i>=x2 && i<=x2+w2 && j>=y2 && j<=y2+h2) return true;
		}
	}
	for(int i=x2; i<=x2+w2; i+=w2){
		for(int j=y2; j<=y2+h2; j+=h2){
			if(i>=x1 && i<=x1+w1 && j>=y1 && j<=y1+h1) return true;
		}
	}
	return false;
}


#endif /* FUNCTIONS_H_ */
