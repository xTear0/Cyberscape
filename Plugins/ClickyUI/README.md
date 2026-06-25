# ClickyUI

**A modular, modernized, fully customizable UI plugin for Unreal Engine 5.**

ClickyUI gives you a library of plug-and-play UI widgets — buttons, menus, text fields, and more — backed by a project-wide theming system. Drop in the premade assets, point them at a Style Asset, and ship a polished, consistent interface without writing styling boilerplate.

It stays out of your way. Function names and event bindings mirror the standard Unreal widgets, so everything remains Blueprint-friendly and instantly familiar. Want to react to a button press? `Button->OnClicked` — exactly like a stock UE `UButton`.

---

## Highlights

- **Modular** — every widget is self-contained. Use one, use all of them, mix them with your existing UI.
- **Themeable** — a single `CUI_StyleAsset` defines colors, sounds, and fonts for your whole project. Swap themes by changing one field.
- **Token-driven styling** — the `CUI_StyleServiceComponent` applies named style tokens to any widget at design time, so what you see in the editor is what you ship.
- **Premade content** — the plugin ships with ready-to-use widget assets so you can start immediately.
- **Blueprint-first** — events, getters, and setters are all exposed and named to match Unreal's conventions.
- **No vendor lock-in** — built on standard UMG/Slate. Familiar patterns, no surprises.

---

## Project Status

ClickyUI is actively developed. Most of the library is stable and ready to use, but a few components are still being built out:

| Component | Status |
|-----------|--------|
| `CUI_StyleAsset` / `CUI_StyleServiceComponent` | ✅ Stable |
| `CUI_Button_Wide`, `CUI_Button_Square` | ✅ Stable |
| `CUI_Menu_Dropdown`, `CUI_Menu_Hamburger`, `CUI_Menu_Kebab` | ✅ Stable |
| `CUI_EditableTextBox` | ✅ Stable |
| `CUI_Button_Checkbox`, `CUI_Button_CircleTick`, `CUI_Button_Switchbox` | 🚧 Work in progress |
| `CUI_Toast`, `CUI_Toast_Container` | 🚧 Work in progress |
| `CUI_ProgressBar` | 🚧 Work in progress |

Work-in-progress components are functional but their interfaces may change between versions — use them with that in mind.

---

## Requirements

- Unreal Engine 5
- Modules used: `Core`, `CoreUObject`, `Engine`, `UMG`, `InputCore`, `Slate`, `SlateCore`

---

## Installation

1. Copy the `ClickyUI` folder into your project's `Plugins/` directory (create it if it doesn't exist).
2. Launch your project and let the editor compile the plugin.
3. Open **Edit → Plugins**, find **ClickyUI** under the *Other* category, and confirm it's enabled.
4. Restart the editor if prompted.

The plugin can contain content, so the premade widget assets are available in the **Plugins** view of your Content Browser as soon as it's enabled.

---

## The Theming System

ClickyUI's theming is built from two pieces: a **Style Asset** that stores your design tokens, and a **Style Service Component** that applies them to individual widgets.

### CUI_StyleAsset

A Data Asset that holds one or more named **styles** in its `StyleLibrary`. Each style (`FCUI_Style`) groups your design tokens:

| Token Group | Purpose | Example Keys |
|-------------|---------|--------------|
| `Surfaces` | Background and layered surface colors | `Surface/BG`, `Surface/Raised`, `Surface/Hover` |
| `Grays` | Neutral text and border colors | `Gray/Border`, `Gray/Muted`, `Gray/Primary` |
| `Accents` | Brand accent ramp | `Accent/950` … `Accent/50` |
| `Semantics` | Status colors | `Success`, `Warning`, `Danger`, `Info` (plus matching `*Bg`) |
| `SoundCues` | Named UI sounds | `Button Click`, `Button Hover`, `Error`, `Login` |
| `FontFamilies` | Named font families with default sizes | `Display`, `Body`, `Mono` |

The asset ships with a sensible dark-theme default for every color token, so you have a working palette out of the box — just override what you need.

Set `ActiveTheme` to the name of the style you want live, and the rest of the system reads from it. Convenient lookups are available in Blueprint and C++:

```cpp
FLinearColor    Color = StyleAsset->GetColorByName(TEXT("Accent/600"));
FSlateSound     Sound = StyleAsset->GetSoundByName(TEXT("Button Click"));
FCUI_FontFamily Font  = StyleAsset->GetFontFamilyByName(TEXT("Display"));
```

### CUI_StyleServiceComponent

Add this UI component to any widget to override its color, sound, or font using a named token from a Style Asset. It resolves and applies the tokens during pre-construct, so styling shows correctly in the editor.

- **Color** applies to most widget types — `TextBlock`, `Image`, `Button`, `Border`, `UserWidget`.
- **Sound** (`PressedSoundToken`, `HoverSoundToken`) applies to `UButton`.
- **Font** (`FontFamilyToken`, with an optional `FontSizeOverride`) applies to `UTextBlock`.

Token fields populate as dropdowns sourced directly from the assigned Style Asset, and the component logs a clear warning if a token is set on an incompatible widget type.

---

## Widget Library

### Buttons

| Widget | Description | Key Events |
|--------|-------------|------------|
| `CUI_Button_Wide` | A wide text button. Can act as its own text block via optional bindings, with enable/disable and transition animations. | `OnClicked`, `OnPressed`, `OnReleased`, `OnHovered`, `OnUnhovered`, `OnIsEnabled` |
| `CUI_Button_Square` | An icon button driven by a `UTexture2D`. Supports hover-pulse, click, and selected/deselected animations. | `OnClicked`, `OnClickedPostAnim`, `OnPressed`, `OnReleased`, `OnHovered`, `OnUnhovered` |
| `CUI_Button_Checkbox` 🚧 | A checkbox-style toggle with a configurable default state. | `OnCheckStateChanged` |
| `CUI_Button_CircleTick` 🚧 | A circular tick toggle — same interface as the checkbox, different look. | `OnCheckStateChanged` |
| `CUI_Button_Switchbox` 🚧 | An animated on/off switch with turn-on / turn-off animations. | `OnToggled` |

`CUI_Button_Square` exposes both `OnClicked` (immediate) and `OnClickedPostAnim`, which fires after the click animation finishes — handy for chaining state changes to the visual feedback.

**Buttons double as text blocks.** Where a button includes an internal text block — like `CUI_Button_Wide` — you can drive its label directly with the text functions. `SetText(FText)` and `GetText()` work just like they would on a standalone text widget, so you can treat the button as a text element when you need to. Set the initial label and size in the editor via the `TextContent` and `TextSize` properties. (The text bindings are optional, so a button configured without one still works as a plain button.)

> 🚧 **Work in progress** — `CUI_Button_Checkbox`, `CUI_Button_CircleTick`, and `CUI_Button_Switchbox` are still under active development. Their interfaces may change, and they aren't yet recommended for production use. `CUI_Button_Wide` and `CUI_Button_Square` are stable.

### Menus

| Widget | Description |
|--------|-------------|
| `CUI_Menu_Dropdown` | A classic dropdown. Set a label, an optional expanded-section title, and up to five options. Broadcasts `OnSelectionChanged` with the index and text. Collapses automatically when focus is lost. |
| `CUI_Menu_Hamburger` | An animated hamburger menu. Selections stagger in and out with a configurable `DelayTime`. The collapsed button reflects the active selection. Up to five selections. |
| `CUI_Menu_Kebab` | A compact three-option kebab menu built from square buttons, with selected-state highlighting. |

Each menu uses a paired *Expanded* widget for its open state, and all of them broadcast a strongly-typed selection-changed event you can bind to in Blueprint or override in C++.

### Notifications 🚧

> 🚧 **Work in progress** — the notification toast system is still under active development and not yet recommended for production use.

- **`CUI_Toast`** — a single toast notification with a typed category (`Info`, `Success`, `Warning`, `Error`, `Generic`), a configurable display duration, and show/dismiss animations. Auto-dismisses on a timer, or call `Dismiss()` to close it early.
- **`CUI_Toast_Container`** — manages a stack of toasts. Call `ShowToast(Message, Type, Duration)` to spawn one. Honors a `MaxToasts` limit and evicts the oldest toast when the stack is full.

### Progress 🚧

> 🚧 **Work in progress** — the progress bar is still under active development and not yet recommended for production use.

- **`CUI_ProgressBar`** — supports two modes:
  - **Determinate** — set a precise value with `SetPercent` (clamped 0–1).
  - **Indeterminate** — plays a looping animation for unknown-duration tasks.

  Switch at runtime with `SetMode`.

### Text

- **`CUI_EditableTextBox`** — an editable text field with hint text, an optional password mode, and an `OnTextChanged` event.

---

## Quick Start

1. **Create a Style Asset** — right-click in the Content Browser → *Miscellaneous → Data Asset* → choose `CUI_StyleAsset`. Add a style to the `StyleLibrary`, tweak its tokens, and set `ActiveTheme`. Additionally, use the premade Style Asset, and create your own theme under the default theme.
2. **Drop in a widget** — add one of the premade ClickyUI widgets to your UMG hierarchy (or subclass one).
3. **Theme it** — add a `CUI_StyleServiceComponent` to the widgets you want themed, assign your Style Asset, and pick tokens from the dropdowns.
4. **Wire up events** — bind to the widget's events exactly as you would a stock Unreal widget:

```cpp
// In C++
MyWideButton->OnClicked.AddDynamic(this, &UMyWidget::HandleClick);
```

In Blueprint, the same events appear in the details panel and event graph under the widget's category — no special setup required.

---

## Design Philosophy

ClickyUI intentionally keeps function names and binding patterns identical to Unreal's native widgets. There's nothing new to learn: if you know how to use a `UButton`, you already know how to use a `CUI_Button`. The plugin adds polish, theming, and convenience.

---

## Credits

Created by **Spencer Kotrosa**.

ClickyUI is actively developed, with more features added continually.

Enjoy!
