#!/bin/bash


for file in data/*; do
    filename="${file##*/}"
    mv data/$filename query/
    ./movie_recommender query/$filename data/*
    mv query/$filename data/
done

#move back 






