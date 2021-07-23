# Tổ chức thư mục
- */Release/Bin/Dictionary* là thư mục từ điển chứa các từ được rút trích (**metadata**)
- */Release/File* là thư mục chứa tập dữ liệu người dùng cần tìm kiếm ( **định dạng** : *folder/subfolder/** )
- */Release/Config*
	- *stopwords.txt* (**danh sách stopwords, người dùng có thể chỉnh sửa**)
	- *index.txt* (**chứa thông tin đường dẫn của các văn bản**)

# Non-GUI
Có hai file thực thi chính trong thư mục */Release/Bin*:
-  *ModifyIndex.exe* (**Chương tình xử lý tập tin**)
- 	*Query.exe*
# HDSD Non-GUI
Người dùng thực hiện tuần tự theo các bước dưới đây:
-	Chạy file thực thi *ModifyIndex.exe* để chuẩn bị dữ liệu trước khi truy vấn(***Có thể bỏ qua bước này nếu không cần cập nhật dữ liệu thêm***) .
	-	Các lựa chọn của chương trình:
		-	**Add**: thêm văn bản (ghi thông tin các tập tin chứa văn bản ra */Release/Config/index.txt* -> rút trích **metadata** -> *Dictionary*).
		**Lưu ý** : nhóm đã rút trích sẵn */Release/File/VanBanTV_train* cho người dùng.
		-	**Remove**: xóa dữ liêụ (xóa thông tin các tập tin chứa văn bản trong
*/Release/Config/index.txt* và xóa **metadata** trong *Dictionary*).
		- **Clear**: xóa toàn bộ dữ liệu */Release/Config/index.txt* và *Dictionary*
- Chạy file thực thi *Query.exe* để truy vấn.
	-  Các lựa chọn của chương trình:
		- **Instant Search**: đưa dữ liệu **metadata** cần thiết lên RAM -> truy vấn .
			*(Phù hợp từng truy vấn riêng lẻ)*.
		- **Full Search**: đưa toàn bộ dữ liệu **metadata** lên RAM -> truy vấn.
			*(Nhiều truy vấn)*.
### [Khuyến khích người dùng sử dụng Non-GUI vì đầy đủ tính năng]

# GUI
Giao diện người dùng,  chạy lệnh như bên dưới trong cửa sổ **cmd** và đảm bảo rằng  **Đã cài đặt Python**.
```
python Gui.py
```
*Lưu ý*: Tính năng thêm văn bản trong phiên bản GUI theo định dạng sau: *folder/* *.


