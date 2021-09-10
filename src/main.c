#include <stdio.h>
#include <string.h>
#include <math.h>
#include <setjmp.h>
#include <hpdf/hpdf.h>
#include <sys/socket.h>

jmp_buf env;

static void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no,
						  void *user_data) {
	fprintf(stderr, "ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
			(HPDF_UINT)detail_no);
	longjmp(env, 1);
}

static void insert_name_date(HPDF_Page page) {
	float width = HPDF_Page_GetWidth(page);
	float height = HPDF_Page_GetHeight(page);

	HPDF_Page_SetTextLeading(page, 20);

	HPDF_Rect r = {
		.left = width - 170,
		.top = height,
		.right = width,
		.bottom = height - 250,
	};

	HPDF_Page_SetRGBFill(page, 0.0, 0.0, 0.0);
	HPDF_Page_BeginText(page);
	HPDF_Page_TextRect(page, r.left, r.top - 10, r.right, r.bottom,
					   "Name: _______________________\n"
					   "Date: ________ Period: ______\n",
					   HPDF_TALIGN_LEFT, NULL);
	HPDF_Page_EndText(page);
}

int main(int argc, char **argv) {
	HPDF_Doc pdf = HPDF_New(error_handler, NULL);

	if (!pdf) {
		fprintf(stderr, "Cannot create PDF\n");
		return 1;
	}

	if (setjmp(env)) {
		HPDF_Free(pdf);
		return 1;
	}

	HPDF_Page page = HPDF_AddPage(pdf);
	HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
	HPDF_Font helvetica = HPDF_GetFont(pdf, "Helvetica", NULL);

	HPDF_Page_SetFontAndSize(page, helvetica, 10);
	insert_name_date(page);

	char file_name[128];
	strcpy(file_name, argv[0]);
	strcat(file_name, ".pdf");
	HPDF_SaveToFile(pdf, file_name);

	HPDF_Free(pdf);

	return 0;
}
