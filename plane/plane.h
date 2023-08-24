#ifndef PLANE_H
#define PLANE_H

bool **init_plane();
bool reserve(bool **plane, int row, int seat);
bool cancel(bool** plane, int row, int seat);
void print_plane(bool **plane);

#endif