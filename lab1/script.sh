#!/bin/bash

## Modify the above line to point to bash executable in your system

## ROLL NUMBERS OF THE TEAM-MATES ##
#    1. 111801042
#    2. 111801040
#    3. 111801036
#    4. 111801015
###

## Write your script below this line ##

## our script time to interpret 100 million entries
#
#  real: 3 mins 58.178 seconds
#  user: 10 mins 55.256 seconds
#  sys: 0 mins 7.140 seconds
#
##
function getoutput() {

    #current course position
    f_t=$1

    #total courses
    files_t=$2

    #return value
    retval="0"
    for i in `seq 1 $files_t`;
    do
        #we need columns from file 1 only until the current course position for now
        if [ $(expr $i = $f_t) == 1 ]
        then
            break
        fi
        #add this column as needed columns
        retval="$retval 1.$(expr "$i" + 1)"
    done

    #return the needed columns
    echo "$retval 2.$(expr "$i" + 1)"
}

function joinfolder() {
    #file pattern (CS/ CE/ ME/ EE)
    file_pat=$1

    #output dir
    dir="."
    mkdir -p $dir

    #find files with that pattern
    files=($(find courses -type f -name "${file_pat}*" | sort))

    #iterator to keep track of file count (course count)
    iterator=1
    for f in ${files[@]};
    do
        #this function decides which columns to take in the join function
        retval=$(getoutput $iterator ${#files[@]})

        #join files to main output file of that course, used a temp file named a.csv
        join -1 1 -2 1 -t "," -a 1 -a 2 -o "$retval" "$dir/${file_pat}.csv" "${f}" > "$dir/a.csv"
        iterator=$(expr "$iterator" + "1")
        cat $dir/a.csv > "$dir/${file_pat}.csv"

        #remove temp file
        rm $dir/a.csv
    done
}

#how much data do you need( default is 100 million )
data_count=${1:-100000000}

#where to generate the data
data_file="master.csv"

#clean outputs of prev execution
make clean


#make to generate input generator
make

#generate input
./input_generator $data_count 111801042 111801040 111801036 111801015 > $data_file

#fiter in such a way that if a student obtains different marks in the same course, then take the highest and write back to the master file
sort -r -t "," -nk3 $data_file | sort -u -t "," -k 1,1 -k 2,2 -s -o $data_file

#these are the roll numbers for the branches
branches=("101" "111" "121" "131")

#remove the directories and create them course stores all coursewise csv and output contains the required output

rm -rf courses/
mkdir -p "courses"

#loop through each branch
for roll in ${branches[@]}
do
  #assign the branch depending on roll number
  branch=""
  if [ "$roll" == "101" ] 
  then
    branch="CE"
  elif [ "$roll" == "111" ]
  then
    branch="CS"
  elif [ "$roll" == "121" ]
  then
    branch="EE"
  else
    branch="ME"
  fi

  #get all the students in that branch
  branch_students=$(grep "^${roll}" $data_file | cut -d"," -f1 | sort | uniq)

  #get the header row for that branch
  branch_head=$(grep "^${roll}" $data_file | cut -d"," -f2 | sort | uniq)
  branch_head_row=$(echo $branch_head | sed -e "s/\s/,/g")

  #write the header into the file
  touch "${branch}.csv"

  #store all the courses of that branch in an array
  IFS=',' read -r -a courses <<< "$branch_head_row"

  iterator=0
  course_pos=","

  total_courses=$(expr "${#courses[@]}" - 1)


  #go through each course
  for course in ${courses[@]}
  do
    iterator=$(expr "$iterator" + "1")
    # echo $iterator $course_pos
    #write the course details in the respective csv
    grep "$course" $data_file | cut -d"," -f1,3  > "courses/${course}.csv"
    sed -i "s/,/$course_pos/g" "courses/${course}.csv"

    #from now we decide how many commas to put before and after a course depending on their sorted order to the couurses/course.csv file
    after_commas=""
    remaining_comas=$(expr "$total_courses" - "$iterator")
    for i in `seq 0 $remaining_comas`
    do
        after_commas="$after_commas,"
    done
    #add commas to the end of the file depending on the number of courses in that branch
    sed -i "s/$/$after_commas/g" "courses/${course}.csv"
    course_pos="$course_pos,"
  done

  #if a particular course has no files the continue(this happens when the number of input files generated are very small)
  files_count=$(find "courses/" -type f -name "${branch}*" | wc -l)
  if [ "$files_count" == 0 ]
  then
    continue
  fi
  
  #this funtion uses join to combine all students data
  joinfolder $branch

  #append the header to the first line
  sed -i "1 i\student,$branch_head_row" "${branch}.csv"
done


#since we used courses folder in a different way so as to make join easier, we bring courses to its required form
courses_dir="courses/"

#go through each course file
for f in "$courses_dir*"
do 
    #replace multiple commas with one comma
    sed -i "s/,\{2,\}/,/g" $f
    #replace the last comma in a file with an empty string
    sed -i "s/,$//g" $f
done