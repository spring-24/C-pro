PASS_CONDITION = 60
scores = []

def score_input(scores):
    try:
        score_input = input("추가할 시험 점수를 입력하세요 (0 ~ 100): ")
        score = float(score_input)
        if 0 <= score <= 100:
            scores.append(score)
            print("점수가 추가되었습니다.")
        else:
            print("점수는 0과 100 사이여야 합니다.")
    except ValueError:
        print("유효한 숫자를 입력하세요.")

def score_average(scores):
    if scores:
        total = sum(scores)
        average = total / len(scores)
        return average
    else:
        return None

def check_pass_fail(average, threshold=PASS_CONDITION):
    if average is None:
        print("평균을 계산할 수 없습니다. 점수를 먼저 추가하세요.")
    elif average >= threshold:
        print(f"평균: {average:.2f} / P")
    else:
        print(f"평균: {average:.2f} / F")

def display_scores(scores):
    if scores:
        print("현재 저장된 점수들:")
        for idx, score in enumerate(scores, start=1):
            print(f"{idx}. {score}")
    else:
        print("저장된 점수가 없습니다.")

def main():
    while True:
        print("\n--- 학생 성적 관리 시스템 ---")
        print("1. 점수 추가")
        print("2. 모든 점수 보기")
        print("3. 평균 계산 및 합격 여부 확인")
        print("4. 프로그램 종료")
        
        choice = input("원하는 옵션의 번호를 입력하세요: ")
        
        if choice == '1':
            score_input(scores)
        elif choice == '2':
            display_scores(scores)
        elif choice == '3':
            avg = score_average(scores)
            check_pass_fail(avg)
        elif choice == '4':
            print("프로그램을 종료합니다. 안녕히 가세요!")
            break
        else:
            print("유효하지 않은 옵션입니다. 다시 입력하세요.")

if __name__ == '__main__':
    main()
