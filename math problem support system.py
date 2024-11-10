import tkinter as tk
from tkinter import filedialog, messagebox
import pytesseract
from PIL import Image

# Tesseract 경로 설정 (Tesseract 설치 후 경로 지정 필요)
# pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"  # Windows 경로 예시

class MathSolverApp:
    def __init__(self, root):
        self.root = root
        self.root.title("수학 문제 풀이 프로그램")
        self.root.geometry("400x400")
        
        # 메인 화면 설정
        self.setup_main_screen()

    def setup_main_screen(self):
        self.clear_screen()

        # 학년수준 선택 메뉴
        tk.Label(self.root, text="학년 수준을 선택하세요:").pack(pady=10)
        
        self.grade_var = tk.StringVar()
        self.grade_var.set("중1")  # 기본값 설정
        tk.OptionMenu(self.root, self.grade_var, "중1", "중2", "중3", "고1", "고2", "고3").pack(pady=10)
        
        # 모드 선택 버튼
        tk.Button(self.root, text="모르는 문제 풀이 탐색", command=self.search_solution_mode).pack(pady=10)
        tk.Button(self.root, text="유사 풀이 탐색", command=self.similar_solution_mode).pack(pady=10)

        # 하단 안내 문구 추가
        tk.Label(self.root, text="정재혁 문제자료실", font=("Arial", 10)).pack(side="bottom", pady=10)

    def search_solution_mode(self):
        self.clear_screen()
        
        tk.Label(self.root, text="문제 사진을 첨부하세요").pack(pady=10)
        tk.Button(self.root, text="문제사진 첨부하기", command=self.upload_problem_image).pack(pady=10)
        
        tk.Button(self.root, text="풀이 탐색", command=self.search_solution).pack(pady=10)
        tk.Button(self.root, text="메인 화면으로 돌아가기", command=self.setup_main_screen).pack(pady=10)
        
        tk.Label(self.root, text="정재혁 문제자료실", font=("Arial", 10)).pack(side="bottom", pady=10)

    def similar_solution_mode(self):
        self.clear_screen()
        
        tk.Label(self.root, text="문제 사진을 첨부하세요").pack(pady=10)
        tk.Button(self.root, text="문제사진 첨부하기", command=self.upload_problem_image).pack(pady=10)
        
        tk.Label(self.root, text="내 풀이 사진을 첨부하세요").pack(pady=10)
        tk.Button(self.root, text="내 풀이 사진 첨부하기", command=self.upload_my_solution_image).pack(pady=10)
        
        tk.Button(self.root, text="유사 풀이 탐색", command=self.search_similar_solution).pack(pady=10)
        tk.Button(self.root, text="메인 화면으로 돌아가기", command=self.setup_main_screen).pack(pady=10)
        
        tk.Label(self.root, text="정재혁 문제자료실", font=("Arial", 10)).pack(side="bottom", pady=10)

    def upload_problem_image(self):
        # 문제 사진 경로 선택
        file_path = filedialog.askopenfilename(title="문제 사진 선택", filetypes=[("Image files", "*.png;*.jpg;*.jpeg")])
        if file_path:
            self.problem_image_path = file_path
            messagebox.showinfo("파일 첨부 완료", "문제 사진이 첨부되었습니다.")
        else:
            messagebox.showwarning("파일 첨부 실패", "파일을 선택하지 않았습니다.")

    def upload_my_solution_image(self):
        # 내 풀이 사진 경로 선택
        file_path = filedialog.askopenfilename(title="내 풀이 사진 선택", filetypes=[("Image files", "*.png;*.jpg;*.jpeg")])
        if file_path:
            self.my_solution_image_path = file_path
            messagebox.showinfo("파일 첨부 완료", "내 풀이 사진이 첨부되었습니다.")
        else:
            messagebox.showwarning("파일 첨부 실패", "파일을 선택하지 않았습니다.")

    def search_solution(self):
        if hasattr(self, 'problem_image_path'):
            # 이미지에서 텍스트 추출
            text = pytesseract.image_to_string(Image.open(self.problem_image_path), lang="kor+eng")
            messagebox.showinfo("문제 풀이", f"추출된 텍스트: {text}")
        else:
            messagebox.showwarning("오류", "문제 사진이 첨부되지 않았습니다.")

    def search_similar_solution(self):
        if hasattr(self, 'problem_image_path') and hasattr(self, 'my_solution_image_path'):
            # 이미지에서 텍스트 추출 (유사 풀이 탐색에 활용 가능)
            problem_text = pytesseract.image_to_string(Image.open(self.problem_image_path), lang="kor+eng")
            my_solution_text = pytesseract.image_to_string(Image.open(self.my_solution_image_path), lang="kor+eng")
            messagebox.showinfo("유사 풀이", f"추출된 문제 텍스트: {problem_text}\n내 풀이 텍스트: {my_solution_text}")
        else:
            messagebox.showwarning("오류", "문제 사진 또는 내 풀이 사진이 첨부되지 않았습니다.")

    def clear_screen(self):
        for widget in self.root.winfo_children():
            widget.destroy()

# 프로그램 실행
root = tk.Tk()
app = MathSolverApp(root)
root.mainloop()
