# VietType—Bộ gõ tiếng Việt nguồn mở

## VietType là gì?
VietType là bộ gõ tiếng Việt nguồn mở dành cho Windows 10.

## Tại sao sử dụng VietType?
- VietType là phần mềm nguồn mở. Bất cứ ai có thể sử dụng, sửa đổi và lưu hành VietType theo Giấy phép Công cộng GNU (GNU GPL).
- VietType không chứa quảng cáo, các tính năng theo dõi người dùng, mã độc hay phần mềm gián điệp. Bạn có thể kiểm chứng bằng cách xem mã nguồn của VietType.
- Tôi cung cấp VietType hoàn toàn miễn phí, không vì lợi lộc.
- VietType sử dụng phương thức nhập liệu có sẵn của Windows nên tương thích với nhiều ứng dụng như Chrome, Skype, HTKK, v.v.

## Tôi tải VietType ở đâu?
Bạn có thể tải mã nguồn và bộ cài đặt VietType tại [trang GitHub này](https://github.com/dinhngtu/VietType/releases).

### **Lưu ý**:
**VietType được cung cấp dưới Giấy phép Công cộng GNU**. Nếu bạn lưu hành VietType hay bản sửa đổi của VietType, **bạn phải cung cấp kèm theo Giấy phép này cũng như mã nguồn và mọi thay đổi mã nguồn lên VietType**. Mọi thay đổi lên VietType đều phải sử dụng cùng giấy phép với VietType (GNU GPL).

## Sử dụng VietType như thế nào?
Chạy file MSI để tiến hành cài đặt. Sau khi cài đặt xong, bạn mở chương trình "Enable VietType" trong thư mục Start.

VietType sử dụng cách gõ Telex tự do. VietType thể hiện trạng thái trên thanh ngôn ngữ của Windows bằng biểu tượng "V" hoặc "E". Các phím tắt của VietType như sau:
- Alt-huyền (nút bên trên nút Tab) để bật và tắt VietType;
- Ctrl (trong lúc gõ từ): Kết thúc từ ngay lập tức;
- Esc (trong lúc gõ từ): Huỷ bỏ gõ từ, chuyển về phím được gõ ban đầu.

Nhấn chuột phải vào biểu tượng của VietType để hiện trình đơn lựa chọn của VietType. VietType có những lựa chọn sau:
- "Enabled by default": bật/tắt tiếng Việt khi khởi động máy tính;
- "Use 'oà', 'uý' instead of 'òa', 'úy'": lựa chọn cách bỏ dấu cho các vần "oà", "uý", v.v.;
- "Accept 'd' anywhere": Cho phép gõ "d" để chuyển "d" -> "đ" tại bất cứ nơi nào trong từ.

## Câu hỏi thường gặp
- Tại sao VietType ít tính năng vậy? Tại sao VietType không có các tính năng như gõ tắt, chuyển mã, v.v.? \
Tôi thiết kế VietType để đáp ứng nhu cầu gõ tiếng Việt tối thiểu.

- Tôi có thể sao chép, sửa đổi hay bán lại phần mềm VietType hay không? \
VietType là phần mềm tự do, bạn có thể cung cấp lại và/hoặc chỉnh sửa nó theo những điều khoản của Giấy phép Công cộng GNU phiên bản 3 do Tổ chức Phần mềm Tự do công bố. \
Tóm tắt Giấy phép Công cộng GNU (tham khảo tập tin LICENSE đi kèm VietType để biết chính xác các điều khoản):
  - Bạn được phép sử dụng, sửa đổi và lưu hành VietType và các phiên bản đã sửa đổi của VietType.
  - Khi lưu hành VietType hay các phiên bản đã sửa đổi của VietType:
    - Bạn phải đóng gói kèm theo Giấy phép Công cộng GNU và các thông báo giấy phép trong VietType;
    - Bạn phải cung cấp mã nguồn của VietType và các thay đổi (nếu có);
    - Bất cứ thay đổi nào lên VietType phải sử dụng cùng một giấy phép với VietType (GNU GPL).
  - VietType không cung cấp bất cứ bảo hành hay bảo đảm nào. Bạn tự chấp nhận mọi rủi ro và trách nhiệm khi sử dụng VietType.

## MSI advertisement

MSI advertisement allows delaying the installation of features until they are required, e.g. advertised shortcuts for launching config or installing symbols (via an advertised shortcut to a "Symbols README" document). However, VietType doesn't work well with advertisement. In internal testing, VietType's TIP component had to be installed via CA rather than direct Registry table, since IsProfileActivated() also didn't work correctly without CA-based registration. Yet CAs are naturally incompatible with advertised COM classes, since either the CAs would run before the coclass is registered, or TIP registration would be fragmented between the MSI and another tool (e.g. Config, which would suddenly require admin privileges for registration). Moreover, testing showed that even advertised coclass activation didn't quite work correctly, since the advertised registrar coclass would return E_FAIL on the first time it's activated, requiring a restart of Config. Needless to say, despite being an interesting idea, advertisement just doesn't work for VietType. Another thing to test would be the compatibility of advertised classes with the CA-based system, especially when doing an advertised installation with the `/jm` flag (which to be fair shouldn't be a problem with `AllowAdvertise="no"`).