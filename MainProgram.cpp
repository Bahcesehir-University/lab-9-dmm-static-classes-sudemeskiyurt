#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class IntArray {
private:
int* data;
int capacity;
int count;
public:
IntArray(int cap);
~IntArray();
IntArray(const IntArray& other);
IntArray& operator=(const IntArray& other);
bool add(int value);
int get(int index) const;
int size() const;
int getCapacity() const;
bool isEmpty() const;
bool removeLast();
};
class Tracker {
private:
static int objectCount;
Tracker() = delete;
public:
static void objectCreated();
static void objectDestroyed();
static int getActiveCount();
static void resetCount();
};
int Tracker::objectCount = 0;
void Tracker::objectCreated() {
objectCount++;
}
void Tracker::objectDestroyed() {
objectCount--;
}
int Tracker::getActiveCount() {
return objectCount;
}
void Tracker::resetCount() {
objectCount=0;
}
IntArray::IntArray(int cap) {
data = new int[cap];
capacity=cap;
count=0;
Tracker::objectCreated();
}
IntArray::~IntArray() {
delete[] data;
Tracker::objectDestroyed();
}
IntArray::IntArray(const IntArray& other) {
capacity = other.capacity;
count = other.count;
data = new int[capacity];
for (int i = 0; i < count; i++){
data[i] = other.data[i];
}
Tracker::objectCreated();
}
IntArray& IntArray::operator=(const IntArray& other) {
if (this != &other){
delete[] data;
capacity = other.capacity;
count = other.count;
data = new int[capacity];
for (int i = 0; i< count; i++){
data[i]=other.data[i];
}
}
return *this;
}
bool IntArray::add(int value) {
if (count<capacity){
data[count++]=value;
return true;
}
return false;
}
int IntArray::get(int index) const {
if (index>=0 && index<count){
return data[index];
}
return -1;
}
int IntArray::size() const {
return count;
}
int IntArray::getCapacity() const {
return capacity;
}
bool IntArray::isEmpty() const {
return count==0;
}
bool IntArray::removeLast() {
if (!isEmpty()){
count--;
return true;
}
return false;
}
int main() {
cout << "=== Dynamic Memory & Static Classes Lab ===" << endl;
IntArray arr(5);
cout << "[1] Active objects: " << Tracker::getActiveCount() << endl;
arr.add(10);
arr.add(20);
arr.add(30);
IntArray arr2(arr);
cout << "[4] Active objects after copy: " << Tracker::getActiveCount() << endl;
IntArray arr3(2);
arr3 = arr;
{
IntArray temp(3);
cout << " Inside scope - Active objects: " << Tracker::getActiveCount() << endl;
}
cout << " After scope - Active objects: " << Tracker::getActiveCount() << endl;
return 0;
}
