#!/bin/bash

set -ueo pipefail

resultAVL="";
resultBST="";

function main()
{

    for i in {1..19}
    do

        resultAVL=" $(../target/debug/project_2 --tree AVL < ./benchmark_data_trees/$i)";

        resultBST=" $(../target/debug/project_2 --tree BST < ./benchmark_data_trees/${i}_BST)";

        echo $resultAVL;

        echo $resultBST;

    done

}

main $resultAVL $resultBST