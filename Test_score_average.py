import openpyxl

def get_student_info():
    student_info = {}

    student_info['학번'] = input("학번: ")
    student_info['이름'] = input("이름: ")
    
    subjects = ['국어영역', '수학영역', '영어영역', '한국사영역', '제1탐구영역', '제2탐구영역', 'SW정보영역']
    scores = {}
    detailed_subjects = {}

    for subject in subjects:
        detailed_subject = input(f"{subject} 상세 과목명 입력: ")
        detailed_subjects[subject] = detailed_subject
        score = int(input(f"{subject} {detailed_subject} 점수 입력: "))
        scores[subject] = score

    student_info['scores'] = scores
    student_info['detailed_subjects'] = detailed_subjects
    
    return student_info

def calculate_average(scores):
    total = sum(scores.values())
    return total / len(scores)

def display_results(student_info, average):
    print("\n성적 결과")
    print("학번:", student_info['학번'])
    print("이름:", student_info['이름'])
    
    for subject, detailed_subject in student_info['detailed_subjects'].items():
        score = student_info['scores'][subject]
        print(f"{subject} ({detailed_subject}): {score}")
    
    print(f"\n평균: {average:.2f}")

def save_to_excel(student_info, average):
    filename = f"{student_info['학번']}_{student_info['이름']}_성적.xlsx"
    workbook = openpyxl.Workbook()
    sheet = workbook.active

    sheet.title = "성적 정보"
    sheet.append(["학번", student_info['학번']])
    sheet.append(["이름", student_info['이름']])
    
    sheet.append(["영역", "상세 과목명", "성적"])
    for subject, detailed_subject in student_info['detailed_subjects'].items():
        score = student_info['scores'][subject]
        sheet.append([subject, detailed_subject, score])

    sheet.append(["평균", "", average])
    
    workbook.save(filename)
    print(f"\n엑셀 파일 '{filename}'로 저장되었습니다.")

def main():
    student_info = get_student_info()
    average = calculate_average(student_info['scores'])
    display_results(student_info, average)

    while True:
        print("\n1. 엑셀파일로 저장")
        print("2. 종료하기")
        choice = input("선택: ")

        if choice == '1':
            save_to_excel(student_info, average)
        elif choice == '2':
            print("프로그램을 종료합니다.")
            break
        else:
            print("잘못된 입력입니다. 다시 선택해주세요.")

if __name__ == "__main__":
    main()
