#### IMPORTS ####
import event_manager as EM


def removeBeginningEndSpaces(string: str):

    is_reasonable_space = False
    end_index = len(string)-1
    beginning_index = 0
    result = ""

    while string[end_index] == ' ':
        end_index -= 1

    while string[beginning_index] == ' ':
        beginning_index += 1

    string = string[beginning_index:end_index+1:1]

    beginning_index=0
    end_index = len(string)-1
    while beginning_index <= end_index:
        if string[beginning_index] == ' ' and is_reasonable_space is False:
            is_reasonable_space = True
            result += (string[beginning_index])
            beginning_index += 1
            continue

        if string[beginning_index] == ' ' and is_reasonable_space is True:
            beginning_index += 1
            continue
        else:
            result += (string[beginning_index])
            beginning_index += 1
            is_reasonable_space = False

    temp = len(result)-1
    if result[temp] == '\n':
        temp -= 1
        while result[temp] == ' ':
            temp -= 1
        result = result[0:temp+1:1]
        result += '\n'
    return result


#תחזיר ליסט של סטרינגים
def getNoIdDup(orig_file_path: str):
    result = []
    to_insert = ""

    file = open(orig_file_path, 'r')
    temp_outer_list = []
    temp_inner_list = []
    for line in file:
        if not isValidLine((line)):
            continue
        flag = False
        temp_outer_list = line.split(',')
        for element in result:
            to_insert = element
            temp_inner_list = element.split(',')
            if temp_inner_list[0] == temp_outer_list[0]:
                flag = True
                break
        if flag:
            result[result.index(to_insert)] = line
        else:
            result.append(line)

    file.close()
    return result


def isValidId(student_id: str):
    if student_id[0] == '0' or len(student_id) != 8:
        return False
    return True


def isValidName(name: str):
    if name.replace(' ', '').isalpha():
        return True
    return False


def isValidAge(age: int):
    if 16 <= age <= 120:
        return True
    return False


def isValidYear(age: int, year: int):
    if 2020-year == age:
        return True
    return False


def isValidSemester(semester: int):
    if semester >= 1:
        return True
    return False


# <id (int)>, <name (string)>, <age (int)>, <Year of Birth (int)>, <semester (int)>
def isValidLine(line: str):
    list_line = line.split(',')
    if isValidId(removeBeginningEndSpaces(list_line[0])) and \
            isValidName(removeBeginningEndSpaces(list_line[1])) and \
            isValidAge(int(list_line[2])) and \
            isValidYear(int(list_line[2]), int(list_line[3])) and \
            isValidSemester(int(list_line[4])):
        return True
    return False


def correctLine(line: str):
    result = ""
    commas = 0
    temp_list = line.split(',')
    for element in temp_list:
        result += removeBeginningEndSpaces(element)
        if commas < 4:
            result += ', '
            commas += 1
    return result


#### PART 1 ####
# Filters a file of students' subscription to specific event:
#   orig_file_path: The path to the unfiltered subscription file
#   filtered_file_path: The path to the new filtered file
def fileCorrect(orig_file_path: str, filtered_file_path: str):
    no_id_duplicates_list = getNoIdDup(orig_file_path)
    valid_students_id_list = []
    for line in no_id_duplicates_list:
        if isValidLine(line):
            temp_list = line.split(',')
            if temp_list[0] not in valid_students_id_list:
                valid_students_id_list.append(temp_list[0])
    valid_students_id_list.sort()

    filtered_file = open(filtered_file_path, 'w')
    for id_num in valid_students_id_list:
        for line in no_id_duplicates_list:
            temp_list = line.split(',')
            if temp_list[0] == id_num:
                filtered_file.write(correctLine(line))
                break
    filtered_file.close()
    
    
# Writes the names of the K youngest students which subscribed 
# to the event correctly.
#   in_file_path: The path to the unfiltered subscription file
#   out_file_path: file path of the output file
def printYoungestStudents(in_file_path: str, out_file_path: str, k: int) -> int:
    if k <= 0:
        return -1

    fileCorrect(in_file_path, out_file_path)

    filtered_file = open(out_file_path, 'r')
    ages_list = []
    filtered_students_list = []
    for line in filtered_file:
        temp_ages_list = line.split(',')
        if int(temp_ages_list[2] )not in ages_list:
            ages_list.append(int(temp_ages_list[2]))
    ages_list.sort()
    filtered_file.close()

    for age in ages_list:
        filtered_file = open(out_file_path, 'r')
        for line in filtered_file:
            temp_line = line.split(',')
            if int(temp_line[2]) == int(age):
                filtered_students_list.append(line)
        filtered_file.close()

    # now our list is sorted by age
    # taking care of a case in which there are 2 people (or more) with the same id
    list_len = len(filtered_students_list)
    for j in range(list_len*list_len):
        for i in range(list_len):
            prev = i
            next_index = i + 1
            if i+1 > list_len-1:
                break
            temp_list_prev = filtered_students_list[prev].split(',')
            temp_list_next = filtered_students_list[next_index].split(',')
            if temp_list_prev[2] == temp_list_next[2] and temp_list_prev[0] > temp_list_next[0]:
                filtered_students_list[prev], filtered_students_list[next_index] = filtered_students_list[next_index],\
                                                                                filtered_students_list[prev]
            prev = prev+1
            next_index = next_index+1

    # students list is now fully sorted
    # all we need to do is to print the first k students on the list
    number_of_students = 0
    filtered_file = open(out_file_path, 'w')
    if len(filtered_students_list) <= k:
        for element in filtered_students_list:
            temp_to_print = element.split(',')
            filtered_file.write(removeBeginningEndSpaces(temp_to_print[1]) + '\n')
            number_of_students += 1

    else:
        for i in range(k):
            temp_to_print = filtered_students_list[i].split(',')
            filtered_file.write(removeBeginningEndSpaces(temp_to_print[1]) + '\n')
            number_of_students += 1

    filtered_file.close()

    return number_of_students
    
    
# Calculates the avg age for a given semester
#   in_file_path: The path to the unfiltered subscription file
#   retuns the avg, else error codes defined.
def correctAgeAvg(in_file_path: str, semester: int) -> float:
    if not isValidSemester(semester):
        return -1

    no_id_duplicates_list = getNoIdDup(in_file_path)
    total_sum = 0
    students_num = 0
    for line in no_id_duplicates_list:
        if isValidLine(line):
            temp_list = line.split(',')
            if int(temp_list[4]) == semester:
                total_sum += int(temp_list[2])
                students_num += 1
    if total_sum == 0:
        return 0
    return total_sum/students_num
    

#### PART 2 ####
# Use SWIG :)
# print the events in the list "events" using the functions from hw1
#   events: list of dictionaries
#   file_path: file path of the output file
def printEventsList(events :list,file_path :str): #em, event_names: list, event_id_list: list, day: int, month: int, year: int):
    min_date = events[0]["date"]
    for element in events:
        if EM.dateCompare(element["date"],min_date) < 0:
            min_date = element["date"]
    event_m = EM.createEventManager(min_date)
    for element in events:
        EM.emAddEventByDate(event_m,element["name"], element["date"],element["id"])
    EM.emPrintAllEvents(event_m,file_path)
    return event_m 
    
    
def testPrintEventsList(file_path :str):
    events_lists=[{"name":"New Year's Eve","id":1,"date": EM.dateCreate(30, 12, 2020)},\
                    {"name" : "annual Rock & Metal party","id":2,"date":  EM.dateCreate(21, 4, 2021)}, \
                                 {"name" : "Improv","id":3,"date": EM.dateCreate(13, 3, 2021)}, \
                                     {"name" : "Student Festival","id":4,"date": EM.dateCreate(13, 5, 2021)},    ]
    em = printEventsList(events_lists,file_path)
    for event in events_lists:
        EM.dateDestroy(event["date"])
    EM.destroyEventManager(em)

#### Main #### 
# feel free to add more tests and change that section. 
# sys.argv - list of the arguments passed to the python script
if __name__ == "__main__":
    import sys
    if len(sys.argv)>1:
        testPrintEventsList(sys.argv[1])
