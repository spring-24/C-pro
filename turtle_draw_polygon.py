import turtle

# 정다각형을 그리는 함수
def draw_polygon(sides):
    spring = turtle.Turtle()
    spring.shape('turtle')
    angle = 360 / sides  # 각도 계산
    
    for i in range(sides):
        spring.forward(100)  # 고정된 변의 길이 100
        spring.right(angle)
    
    turtle.done()

# 사용자로부터 정다각형의 변의 개수 입력 받기
sides = int(input("정다각형의 변의 개수를 입력하세요: "))

# 정다각형 그리기
draw_polygon(sides)
