import math
import serial
import customtkinter as ctk
from tkinter import Canvas, font

# =========================
# SERIAL CONFIG
# =========================

SERIAL_PORT = "COM6"
BAUD_RATE = 115200

# =========================
# UI CONFIG
# =========================

ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

# =========================
# MAIN WINDOW
# =========================

app = ctk.CTk()

app.title("Intelligent Cockpit Dashboard")

app.geometry("1200x700")

app.configure(fg_color="#08090d")

# =========================
# SERIAL CONNECTION
# =========================

ser = serial.Serial(SERIAL_PORT,
                    BAUD_RATE,
                    timeout=1)

# =========================
# COLOR PALETTE
# =========================

ACCENT_CYAN    = "#00d4ff"
ACCENT_ORANGE  = "#ff6b2b"
PANEL_BG       = "#0d1117"
CARD_BG        = "#111620"
BORDER_COLOR   = "#1e2a3a"
TEXT_PRIMARY   = "#e8edf5"
TEXT_MUTED     = "#5a6a80"
TICK_COLOR     = "#2a3a4e"
ARC_TRACK      = "#1a2535"

# =========================
# GAUGE CLASS
# =========================

class Gauge:

    def __init__(self,
                 parent,
                 title,
                 unit,
                 accent_color,
                 x,
                 y):

        self.accent = accent_color
        self.title  = title
        self.unit   = unit

        self.canvas = Canvas(
            parent,
            width=360,
            height=380,
            bg="#08090d",
            highlightthickness=0
        )

        self.canvas.place(x=x, y=y)

        self.cx = 180
        self.cy = 195
        self.r  = 130

        self.arc_item   = None
        self.needle     = None
        self.value_text = None
        self.glow_ring  = None

        self._draw_base()
        self.update_value(0)

    # ---- static chrome ----

    def _draw_base(self):

        # outer dark ring
        self.canvas.create_oval(
            self.cx - self.r - 18,
            self.cy - self.r - 18,
            self.cx + self.r + 18,
            self.cy + self.r + 18,
            outline=BORDER_COLOR,
            width=1
        )

        # track arc (drawn as a thick ring simulation with many segments)
        steps = 270
        start_deg = 225
        for i in range(steps):
            a0 = math.radians(start_deg - i)
            a1 = math.radians(start_deg - i - 1.5)
            r_out = self.r + 8
            r_in  = self.r - 8
            pts = [
                self.cx + r_out * math.cos(a0),
                self.cy - r_out * math.sin(a0),
                self.cx + r_out * math.cos(a1),
                self.cy - r_out * math.sin(a1),
                self.cx + r_in  * math.cos(a1),
                self.cy - r_in  * math.sin(a1),
                self.cx + r_in  * math.cos(a0),
                self.cy - r_in  * math.sin(a0),
            ]
            self.canvas.create_polygon(
                pts,
                fill=ARC_TRACK,
                outline=""
            )

        # tick marks
        for i in range(0, 101, 10):
            angle  = math.radians(225 - (i * 2.7))
            is_maj = (i % 20 == 0)
            r_out  = self.r + 6
            r_in   = self.r - (10 if is_maj else 5)
            x1 = self.cx + r_out * math.cos(angle)
            y1 = self.cy - r_out * math.sin(angle)
            x2 = self.cx + r_in  * math.cos(angle)
            y2 = self.cy - r_in  * math.sin(angle)
            self.canvas.create_line(
                x1, y1, x2, y2,
                fill=self.accent if is_maj else TICK_COLOR,
                width=2 if is_maj else 1
            )
            if is_maj:
                tx = self.cx + (self.r - 28) * math.cos(angle)
                ty = self.cy - (self.r - 28) * math.sin(angle)
                self.canvas.create_text(
                    tx, ty,
                    text=str(i),
                    fill=TEXT_MUTED,
                    font=("Consolas", 9)
                )

        # inner circle decoration
        self.canvas.create_oval(
            self.cx - 55, self.cy - 55,
            self.cx + 55, self.cy + 55,
            outline=BORDER_COLOR,
            width=1
        )
        self.canvas.create_oval(
            self.cx - 52, self.cy - 52,
            self.cx + 52, self.cy + 52,
            outline="#0a1018",
            fill="#0a1018"
        )

        # title label — above center
        self.canvas.create_text(
            self.cx,
            self.cy - 20,
            text=self.title,
            fill=TEXT_MUTED,
            font=("Consolas", 10)
        )

        # unit label — below value placeholder
        self.canvas.create_text(
            self.cx,
            self.cy + 32,
            text=self.unit,
            fill=TEXT_MUTED,
            font=("Consolas", 9)
        )

        # bottom label bar
        self.canvas.create_rectangle(
            self.cx - 60, 345,
            self.cx + 60, 367,
            fill=CARD_BG,
            outline=BORDER_COLOR,
            width=1
        )
        self.canvas.create_text(
            self.cx, 356,
            text=self.title,
            fill=self.accent,
            font=("Consolas", 10, "bold")
        )

    # ---- dynamic update ----

    def update_value(self, value):

        value = max(0, min(100, value))

        angle_deg = 225 - (value * 2.7)
        angle     = math.radians(angle_deg)

        # colored arc fill
        if self.arc_item:
            self.canvas.delete(self.arc_item)

        filled_steps = int(value * 2.7)
        start_deg    = 225

        # Draw filled arc as polygon segments
        for i in range(filled_steps):
            frac = i / 270.0
            # interpolate color from dim to bright accent
            a0 = math.radians(start_deg - i)
            a1 = math.radians(start_deg - i - 1.5)
            r_out = self.r + 8
            r_in  = self.r - 8
            pts = [
                self.cx + r_out * math.cos(a0),
                self.cy - r_out * math.sin(a0),
                self.cx + r_out * math.cos(a1),
                self.cy - r_out * math.sin(a1),
                self.cx + r_in  * math.cos(a1),
                self.cy - r_in  * math.sin(a1),
                self.cx + r_in  * math.cos(a0),
                self.cy - r_in  * math.sin(a0),
            ]
            # fade from dim to accent as value increases
            alpha = int(80 + 175 * frac)
            r_ch  = int(self.accent[1:3], 16)
            g_ch  = int(self.accent[3:5], 16)
            b_ch  = int(self.accent[5:7], 16)
            r_dim = max(0, int(r_ch * 0.18))
            g_dim = max(0, int(g_ch * 0.18))
            b_dim = max(0, int(b_ch * 0.18))
            r_f   = int(r_dim + (r_ch - r_dim) * frac)
            g_f   = int(g_dim + (g_ch - g_dim) * frac)
            b_f   = int(b_dim + (b_ch - b_dim) * frac)
            color = f"#{r_f:02x}{g_f:02x}{b_f:02x}"
            tag = f"arc_{i}"
            self.canvas.create_polygon(
                pts,
                fill=color,
                outline="",
                tags="arc_fill"
            )

        self.arc_item = "arc_fill"

        # needle
        if self.needle:
            self.canvas.delete(self.needle)

        nx = self.cx + (self.r - 32) * math.cos(angle)
        ny = self.cy - (self.r - 32) * math.sin(angle)

        # needle base wing
        wing_angle = angle + math.pi / 2
        wx = 6 * math.cos(wing_angle)
        wy = 6 * math.sin(wing_angle)

        self.needle = self.canvas.create_polygon(
            self.cx + wx, self.cy - wy,
            nx, ny,
            self.cx - wx, self.cy + wy,
            fill=self.accent,
            outline=""
        )

        # needle center cap
        self.canvas.create_oval(
            self.cx - 7, self.cy - 7,
            self.cx + 7, self.cy + 7,
            fill="#1a2535",
            outline=self.accent,
            width=1
        )
        self.canvas.create_oval(
            self.cx - 3, self.cy - 3,
            self.cx + 3, self.cy + 3,
            fill=self.accent,
            outline=""
        )

        # digital readout
        if self.value_text:
            self.canvas.delete(self.value_text)

        self.value_text = self.canvas.create_text(
            self.cx,
            self.cy + 10,
            text=f"{value:03d}",
            fill=TEXT_PRIMARY,
            font=("Consolas", 26, "bold")
        )

# =========================
# CREATE GAUGES
# =========================

speed_gauge = Gauge(
    app,
    "SPEED",
    "km/h",
    ACCENT_CYAN,
    30,
    60
)

attention_gauge = Gauge(
    app,
    "FATIGUE",
    "level",
    ACCENT_ORANGE,
    410,
    60
)

# =========================
# RIGHT PANEL
# =========================

panel = ctk.CTkFrame(
    app,
    width=310,
    height=580,
    fg_color=CARD_BG,
    corner_radius=8,
    border_width=1,
    border_color=BORDER_COLOR
)

panel.place(x=858, y=60)

# panel header bar
header = ctk.CTkFrame(
    panel,
    width=310,
    height=46,
    fg_color="#0d1520",
    corner_radius=0
)
header.pack(fill="x")

ctk.CTkLabel(
    header,
    text="◈  SYSTEM STATUS",
    font=("Consolas", 13, "bold"),
    text_color=ACCENT_CYAN
).pack(pady=12)

# divider line
ctk.CTkFrame(
    panel,
    height=1,
    fg_color=BORDER_COLOR
).pack(fill="x")

# risk score card
risk_card = ctk.CTkFrame(
    panel,
    fg_color="#0a1018",
    corner_radius=6,
    border_width=1,
    border_color=BORDER_COLOR
)
risk_card.pack(padx=16, pady=(20, 8), fill="x")

ctk.CTkLabel(
    risk_card,
    text="RISK SCORE",
    font=("Consolas", 10),
    text_color=TEXT_MUTED
).pack(pady=(12, 0))

risk_label = ctk.CTkLabel(
    risk_card,
    text="0",
    font=("Consolas", 48, "bold"),
    text_color=TEXT_PRIMARY
)
risk_label.pack(pady=(0, 12))

# status card
status_card = ctk.CTkFrame(
    panel,
    fg_color="#0a1018",
    corner_radius=6,
    border_width=1,
    border_color=BORDER_COLOR
)
status_card.pack(padx=16, pady=8, fill="x")

ctk.CTkLabel(
    status_card,
    text="DRIVE STATE",
    font=("Consolas", 10),
    text_color=TEXT_MUTED
).pack(pady=(12, 0))

state_label = ctk.CTkLabel(
    status_card,
    text="● SAFE",
    font=("Consolas", 22, "bold"),
    text_color="#00ff88"
)
state_label.pack(pady=(4, 12))

# emergency card
emg_card = ctk.CTkFrame(
    panel,
    fg_color="#0a1018",
    corner_radius=6,
    border_width=1,
    border_color=BORDER_COLOR
)
emg_card.pack(padx=16, pady=8, fill="x")

ctk.CTkLabel(
    emg_card,
    text="ALERT",
    font=("Consolas", 10),
    text_color=TEXT_MUTED
).pack(pady=(12, 0))

emergency_label = ctk.CTkLabel(
    emg_card,
    text="— NORMAL —",
    font=("Consolas", 16, "bold"),
    text_color=TEXT_MUTED
)
emergency_label.pack(pady=(4, 12))

# bottom status bar strip
bar = ctk.CTkFrame(
    panel,
    fg_color="#060a10",
    corner_radius=0,
    height=36
)
bar.pack(fill="x", side="bottom", pady=(8, 0))

ctk.CTkLabel(
    bar,
    text="⬤  LIVE",
    font=("Consolas", 10),
    text_color="#00ff88"
).pack(side="left", padx=14, pady=8)

ctk.CTkLabel(
    bar,
    text="v1.0  CAN-BUS",
    font=("Consolas", 10),
    text_color=TEXT_MUTED
).pack(side="right", padx=14, pady=8)

# =========================
# STATE DECODER
# =========================

def decode_state(state):

    if state == 0:
        return ("● SAFE",     "#00ff88")

    elif state == 1:
        return ("● CAUTION",  "#f5c518")

    elif state == 2:
        return ("● WARNING",  "#ff8c00")

    elif state == 3:
        return ("● CRITICAL", "#ff2222")

    else:
        return ("● FAILSAFE", "#ff2222")

# =========================
# UPDATE LOOP
# =========================

def update_dashboard():

    try:

        line = ser.readline().decode().strip()

        if line:

            values = line.split(",")

            if len(values) == 5:

                speed      = int(values[0])
                attention  = int(values[1])
                risk       = int(values[2])
                state      = int(values[3])
                emergency  = int(values[4])

                speed_percent = int(
                    (speed / 4095) * 100
                )

                attention_percent = int(
                    (attention / 4095) * 100
                )

                speed_gauge.update_value(
                    speed_percent
                )

                attention_gauge.update_value(
                    attention_percent
                )

                risk_label.configure(
                    text=f"{risk}"
                )

                state_text, color = decode_state(
                    state
                )

                state_label.configure(
                    text=state_text,
                    text_color=color
                )

                if emergency == 1:

                    emergency_label.configure(
                        text="⚠  EMERGENCY ACTIVE",
                        text_color="#ff2222"
                    )

                else:

                    emergency_label.configure(
                        text="— NORMAL —",
                        text_color=TEXT_MUTED
                    )

    except:
        pass

    app.after(100, update_dashboard)

# =========================
# START LOOP
# =========================

update_dashboard()

app.mainloop()