#pragma once

#include <list>
#include <iostream>
#include <string>
#include <iostream>
#include <vector>


template<typename T>
struct Node
{
	T data;
	int key;
	int height;
	Node* left;
	Node* right;
	Node(int _key) : key(_key), height(1), left(NULL), right(NULL) {}
	Node(T data, int key)
	{
		this->key = key;
		this->data = data;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

template <typename T>
class AVLTree
{
	Node<T>* Top;
public:
	AVLTree() : Top(NULL) {}
	int Height(Node<T>* El)
	{
		if (El == NULL)
			return 0;
		return  El->height;
	}

	int BalanceFactor(Node<T>* El)
	{
		return (Height(El->right) - Height(El->left));
	}
	Node<T>* FindMin(Node<T>* El)
	{
		if (El->left == NULL)
			return El;
		else
			return FindMin(El->left);
	}
	void  CorrectHeight(Node<T> *El)
	{
		int h_left = Height(El->left);
		int h_right = Height(El->right);
		El->height = ((h_left > h_right) ? h_left : h_right) + 1;
	}
	Node<T> * LeftRotation(Node<T>* El)
	{
		Node<T> * newroot = El->right;
		El->right = newroot->left;
		newroot->left = El;
		CorrectHeight(El);
		CorrectHeight(newroot);
		return newroot;
	}
	Node<T> * RightRotation(Node<T> * El)
	{
		Node<T> * newroot = El->left;
		El->left = newroot->right;
		newroot->right = El;
		CorrectHeight(El);
		CorrectHeight(newroot);
		return newroot;
	}
	Node<T>* Balance(Node<T>* El)
	{
		CorrectHeight(El);
		if (BalanceFactor(El) == -2)
		{
			if (BalanceFactor(El->right) < 0)
				El->right = RightRotation(El->right);

			El = LeftRotation(El);
		}
		else if (BalanceFactor(El) == -2)
		{
			if (BalanceFactor(El->left) > 0)
				El->left = LeftRotation(El->left);
			El = RightRotation(El);
		}
		return El;
	}
	Node<T>* FindEl(Node<T>* El, int key)
	{
		while (El != NULL)
		{
			if (key < El->key)
				El = El->left;
			else if (key > El->key)
				El = El->right;
			else
				return El;
		}
		throw "Error";
	}
	Node<T>* InsertEl(Node<T>* El, T data, int key)
	{
		if (El == NULL)
			return new Node<T>(key, data);
		if (key < El->key)
			El->left = InsertEl(El->left, data, key);
		else
			El->right = InsertEl(El->right, data, key);
		return Balance(El);
	}
	Node<T>* RemoveMin(Node<T>* El)
	{
		if (El->left == NULL)
			return El->right;
		else
			El->left = RemoveMin(El->left);
		return Balance(El);
	}
	Node<T>* Remove(Node<T>* El, int key)
	{
		if (El == NULL)
			return El;
		if (key < El->key)
			El->left = Remove(El->left, key);
		else if (key > El->key)
			El->right = Remove(El->right, key);
		else
		{
			Node<T> * Elleft = El->left;
			Node<T> * ElRight = El->right;
			delete El;
			if (ElRight == NULL)
				return Elleft;
			Node<T> * min = FindMin(ElRight);
			min->right = RemoveMin(ElRight);
			min->left = Elleft;
			return Balance(min);
		}
		return Balance(El);
	}
	T Find(int key)
	{
		Node<T>* El = FindEl(Top, key);
		return El->data;
	}
	void Insert(T data, int key)
	{
		Top = InsertEl(Top, data, key);
	}
	void Delete(int key)
	{
		Top = Remove(Top, key);
	}
	~AVLTree() {}
};
