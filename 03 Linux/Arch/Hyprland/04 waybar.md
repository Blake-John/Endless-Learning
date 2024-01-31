配置 `waybar` 是一个工作量很大的事情，其配置文件存放在 `~/.config/waybar/` 下，最主要的配置文件为 `config.jsonc` 和 `style.css` 。其中， `config.jsonc` 是用来配置其结构及模块的，而 `style.css` 是用来设置 `waybar` 的样式的。

> [!attention] 
> 不管你配置什么，建议先选一个自己比较喜欢的主题，在通过那个主题的配置文件来修改，这样可以省去不少功夫。

# 4.1 `config.jsonc` 

## 4.1.2 基本配置

下面列出了一些基本的全局配置，其中我们在最开始需要更改的是 `layer` ，使得waybar能够展示在最上一层。

| option | typeof | default | description |
| ---- | ---- | ---- | ---- |
| `layer` | string | `bottom` | Decide if the bar is displayed **in front (`top`) of** the windows or **behind (`bottom`) them.** |
| `output` | array | | The output screen to show the waybar|
| `position` | string | `top` | Bar **position**, can be `top`,`bottom`,`left`,`right`. |
|`height`|integer||**Height** to be used by the bar if possible, leave blank for a dynamic value.|
|`width`|integer||**Width** to be used by the bar if possible, leave blank for a dynamic value.|
|`modules-left`|array||Modules that will be displayed on the left.|
|`modules-center`|array||Modules that will be displayed in the center.|
|`modules-right`|array||Modules that will be displayed on the right.|
|`spacing`|integer|`4`|Size of gaps in between of the different modules.|

而有两个配置，是我们开始美化的 **重中之重** ：

- `include` : 
	- **type** : array
	- **description** : 
		- Paths to **additional configuration files**.
		- Each file can contain a single object with any of the bar configuration options. In case of duplicate options, the first defined value takes precedence, i.e. including file -> first included file -> etc. Nested includes are permitted, but make sure to **avoid circular imports**.
		- For a multi-bar config, the `include` directive **affects only current bar configuration object**.
- `reload_style_on_change` : 
	- **type** : bool
	- **description** : 
		- Option to **enable reloading the css style if a modification is detected** on the style sheet file or any imported css files.

`include` 模块能让我们最大程度地 **扩展我们所需要的配置** ，而 `reload_style_on_change` 则可以让我们 **实时** 看到我们修改后的样式，而免去看不到而且需要不断重新加载的烦恼。

## 4.1.2 模块配置

waybar上所展示的一个个图标都是一个 **模块** 。

### 1. 鼠标事件

而对于模块而言，我们支持 **鼠标点击事件** 。

| option | typeof | default | description |
| ---- | ---- | ---- | ---- |
| `on-click` | string |  | Command to execute when you left click on the module |
| `on-click-release` | string |  | Command to execute when you release left button on module |
| `on-double-click` | string |  | Command to execute when you double left click on the module |
| `on-click-middle` | string |  | Command to execute when you middle click on the module using mousewheel |

并且，鼠标点击也分 **左右键** 以及 **是否松开按键** 。没有 `right` 描述的为左键，有则为右键。

| option  | typeof  | default  | description  |
|---|---|---|---|
|`on-click-right`|string||Command to execute when you right click on the module|
|`on-click-right-release`|string||Command to execute when you release right button on the module|

### 2. 配置命令

It is **possible** to specify module actions(if module supports them) **under "actions" block**. Supported actions are described at module definition pages. Example:

```json
"clock": {
    "actions": {
	    "on-click-right": "mode",
        "on-scroll-up": "shift_up",
        "on-scroll-down": "shift_down"
    }
}
```

### 3. 模块显示格式

在模块中设置 `format` 可以设置其显示格式，并且可以使用 `{variable}` 来格式化显示想要的内容，就如同 `Python` 一样。

```json
"format": "{icon} {capacity}%",
"format-icons": ["ﱉ","ﱊ","ﱌ","ﱍ","ﱋ"]
```

### 4. 多实体模块

If you want to have a **second instance** of a module, you can **suffix it by a '#' and a custom name**.

For example if you want a second battery module, you can add `"battery#bat2"` to your modules.

To configure the newly added module, you then also **add a module configuration with the same name**.

This could then look something like this _(this is an incomplete example)_:

```json
"modules-right": ["battery", "battery#bat2"],
"battery": {
    "bat": "BAT1"
},
"battery#bat2": {
    "bat": "BAT2"
}
```

To style in `styles.css` use :

```css
battery.bat2 {
    border-bottom: 2px solid #FFFFFF;
}
```

### 5. 多样式waybar

我们可以将 **不同显示器上的waybar样式设置为一样** ，例如：

```json
{
    "layer": "top",
    "output": "eDP-1",
    "modules-left": ["sway/workspaces", "sway/mode"],
    //...
}
{
    "layer": "top",
    "output": ["eDP-1", "VGA"],
    "modules-left": ["sway/workspaces", "sway/mode"],
    //...
}
```

我们也可以设置 **不同的输出样式** 到 **不同显示器上** ，例如：

```json
[{
    "layer": "top",
    "output": "eDP-1",
    "modules-left": ["sway/workspaces", "sway/mode"],
    //...
}, {
    "layer": "top",
    "output": "VGA",
    "modules-right": ["clock"],
    //...
}]
```

你也可以通过使用 **一些标志语言 (exclamation mark)** 来设置样式，如：

```json
[{
    "layer": "top",
    "output": "eDP-1",
    "modules-left": ["sway/workspaces", "sway/mode"],
    //...
}, {
    "layer": "top",
    "output": "!eDP-1",
    "modules-right": ["clock"],
    //...
}]
```

上面那样设置就会将 `clock` 模块设置在任何 **除了 `eDP-1` 的显示器上** 。

> [!attention] 
> 千万不要将不同的样式设置在同一个显示屏上！！！

### 6. 模块旋转

When positioning Waybar **on the left or right side of the screen,** sometimes it's useful to be able to rotate the contents of a module so the text runs vertically. This can be done using the "rotate" property of the module. Example:

```json
{
    "clock": {
        "rotate": 90
    }
}
```

`rotate` property can be : `0` , `90` , `180` , `270` .

### 7. 添加外部模块设置

You probably want to **share the same formatting and properties** for repeated modules across bars. Put the shared configuration in another file, say, `default-modules.json` : 

```json
{
	"clock": {
		"tooltip-format": "<big>{:%Y %B}</big>\n<tt><small>{calendar}</small></tt>",
		"format": "{:%F %T}",
		"format-alt": "{:%F %T}",
		"interval": 1
	},

}
```

and just import it from `config` : 

```json
[{
	"layer": "top",
	"position": "bottom",
	"output": ["DP-1"],

	"include": [
		"~/.config/waybar/default-modules.json",
	],
	"modules-right": [
		"clock",
		"temperature",
	]
},
{
	"layer": "top",
	"position": "bottom",
	"output": ["HDMI-1"],

	"include": [
		"~/.config/waybar/default-modules.json",
	],
	"modules-right": [
		"clock",
	]

	"clock": {
		"on-click": "do_something",
	}
},
]
```

### 8. 多 waybar 模块

Using `name` field you can call it from the style.css file, like this :  (config file)

```json
{
  "name": "bar1"
   // desired settings
} 
{ 
 "name": "bar2"
 // desired settings
} 
```

In your style.css, you may want to call like this : 

```css
bar1 { 
  font-family: Arimo Nerd Font;
  font-size: 16px;
} 
bar2 {
  font-family: Roboto;
  font-size: 16px;
} 
```

If your bars **share the same modules**, you can specify like this : 

```css
window.bar1#waybar { 
  background-color: rgba(10, 9, 10, 0.87);
} 

window.bar2#waybar {
  background-color: transparent;
} 
```



# 4.2 `style.css` 

## 4.2.1 状态栏样式

The **main waybar window** can be styled with the following:

- `window#waybar`
- `window#waybar.hidden`
- `window#waybar.<name>`
    - `<name>` is set to the value of the _optional_ `name` configuration property. If not set, this class is not available. For more information see [Bar Config](https://github.com/Alexays/Waybar/wiki/Configuration#bar-config)
- `window#waybar.<position>`
    - `<position>` is set to the value of the `position` configuration property. For more information see [Bar Config](https://github.com/Alexays/Waybar/wiki/Configuration#bar-config) (Author Wiki) or [Config](04%20waybar#4.1`config.jsonc`) 

## 4.2.2 模块组样式

Each module group can be styled individually with the following:

- `.modules-left`
- `.modules-center`
- `.modules-right`

## 4.2.3 全局/默认样式

The main waybar windows carry a class tag with the name of the output this window is shown on. This can be used to apply different styles depending on the output. E.g.,

```css
* { font-size: 13px; }
window.eDP-1 * { font-size: 10px; }
```

will set the default font size of all elements to 13px unless overridden later on, but apply a base font size of 10px to all elements on the eDP-1 output (typically, the laptop screen). Note that only the top-level window container has the output assigned in the class tags, not each individual object.

## 4.2.4 动态配置

GTK is used to apply styles and works with [a limited subset of CSS](https://docs.gtk.org/gtk3/css-properties.html).

You can use `env GTK_DEBUG=interactive waybar` to inspect objects and find their CSS classes, experiment with live CSS styles, and lookup the current value of CSS properties.

![Interactive CSS Editor](Interactive%20CSS%20Editor.png)

See [https://wiki.gnome.org/action/show/Projects/GTK/Inspector](https://wiki.gnome.org/action/show/Projects/GTK/Inspector) for more information.

## 4.2.5 查看组件列表

Like the GTK inspector above, Waybar itself can also tell you what GTK widgets with what classes are available for styling (since [#927](https://github.com/Alexays/Waybar/pull/927)). To get this information, simply run Waybar with debug logging enabled: `waybar -l debug` . Each enabled bar's widget tree will be separately logged to the console.

# 4.3 Workspaces

The `workspaces` module displays the current active workspaces in your Wayland compositor.

## 4.3.1 Config

| option | typeof | default | description |
| ---- | :--: | :--: | ---- |
| `format` | string | `{name}` | The format, **how information should be displayed**. |
| `format-icons` | array |  | Based on the workspace name and state, the corresponding icon gets selected.  <br>See [`Icons`](https://github.com/Alexays/Waybar/wiki/Module:-Workspaces#module-workspaces-config-icons) |
| `sort-by-name` | bool | `true` | Should workspaces be sorted by name. |
| `sort-by-coordinates` | bool | `true` | Should workspaces be sorted by coordinates. Note that if both _sort-by-name_ and _sort-by-coordinates_ are true sort by name will be first. If both are false - sort by id will be performed. |
| `sort-by-number` | bool | `false` | If set to true, workspace names will be sorted numerically. Takes presedence over any other sort-by option. |
| `active-only` | bool | `false` | If set to true only active or urgent workspaces will be shown. |
| `persistent-workspaces` | json (see below) | empty | **Lists workspaces that should always be shown**, even when non existant. Doesn't work when `all-outputs` is true |

### 1. Sort

How to sort workspaces.

|name|note|
|---|---|
|`default`|Default hyprland/workspaces sorting algorithm with custom prioritization|
|`id`|Sort workspaces by id|
|`name`|Sort workspaces by name|
|`number`|Sort workspaces by number|

### 2. Icons

Additional to workspace name matching, the following `format-icons` can be set.

|port name|note|
|---|---|
|`active`|Will be shown when workspace is active|
|`default`|Will be shown when no string matches is found.|
|`empty`|Will be shown on active empty workspaces|
|`persistent`|Will be shown on non-active persistent workspaces|
|`special`|Will be shown on non-active special workspaces|
|`urgent`|Will be shown on non-active urgent workspaces|

## 4.3.2 Format Replacemants

| string | replacement |
| ---- | ---- |
| `{name}` | Name of workspace assigned by compositor. |
| `{icon}` | Icon, as defined in _format-icons_. |
| `{windows}` | All windows representations (ex. window icons) as configured by the user, separated by whichever separator the user configured. |

## 4.3.3 Persistent Workspaces : 

Each entry of `persistent-workspace` names a workspace that should **always be shown**. Associated with that value is **a list of outputs indicating _where_ the workspace should be shown**, an **empty list denoting all outputs**.

```json
"wlr/workspaces": {
    "persistent-workspaces": {
        "3": [], // Always show a workspace with name '3', on all outputs if it does not exists
        "4": ["eDP-1"], // Always show a workspace with name '4', on output 'eDP-1' if it does not exists
        "5": ["eDP-1", "DP-2"] // Always show a workspace with name '5', on outputs 'eDP-1' and 'DP-2' if it does not exists
    }
}
```

### Example

```json
"hyprland/workspaces": {
  "format": "{icon}",
  "on-click": "activate",
  "format-icons": {
    "1": "",
    "2": "",
    "3": "",
    "4": "",
    "5": "",
    "urgent": "",
    "active": "",
    "default": ""
  },
  "sort-by-number": true
}
```

## 4.3.4 Style

The way the CSS is evaluated you need to order it in order of importance with last taking precedent.

- _#workspaces_
- _#workspaces button_
- _#workspaces button.active_
- _#workspaces button.empty_
- _#workspaces button.persistent_
- _#workspaces button.special_
- _#workspaces button.visible_ 
- _#workspaces button:hover_ : 鼠标悬停时的样式


# 4.4 Hardware

## 4.4.1 CPU

The `cpu` module displays the current cpu utilization.

### 1. Config

Addressed by `cpu`

|option|typeof|default|description|
|---|---|---|---|
|`interval`|integer|10|The interval in which the information gets polled.|
|`format`|string|`{usage}%`|The format, how information should be displayed. On `{}` data gets inserted.|
|`max-length`|integer||The maximum length in character the module should display.|
|`rotate`|integer||Positive value to rotate the text label.|
|`states`|array||A number of cpu usage states which get activated on certain usage levels.  <br>See [States](https://github.com/Alexays/Waybar/wiki/States)|
|`on-click`|string||Command to execute when clicked on the module.|
|`on-click-middle`|string||Command to execute when you middle clicked on the module using mousewheel.|
|`on-click-right`|string||Command to execute when you right clicked on the module.|
|`on-scroll-up`|string||Command to execute when scrolling up on the module.|
|`on-scroll-down`|string||Command to execute when scrolling down on the module.|
|`smooth-scrolling-threshold`|double||Threshold to be used when scrolling.|
|`tooltip`|bool|`true`|Option to enable tooltip on hover.|

### 2. Format Replacements

|string|replacement|
|---|---|
|`{load}`|Current cpu load.|
|`{usage}`|Current cpu usage (% view).|
|`{usageN}`|_Nth_ cpu core usage (% view).|
|`{icon}`|Current cpu usage (icon view).|
|`{iconN}`|_Nth_ cpu core usage (icon view).|
|`{avg_frequency}`|Current cpu average frequency (based on all cores) in GHz.|
|`{max_frequency}`|Current cpu max frequency (based on the core with the highest frequency) in GHz.|
|`{min_frequency}`|Current cpu min frequency (based on the core with the lowest frequency) in GHz.|

```json
"cpu": {
	"interval": 10,
	"format": " {usage}%",
	"max-length": 10,
	"on-click": "kitty --start-as=fullscreen --title btop sh -c 'btop'",
	"format": "{icon0} {icon1} {icon2} {icon3} {icon4} {icon5} {icon6} {icon7}",
	"format-icons": [">▁<", ">▂<", ">▃<", ">▄<", ">▅<", ">▆<", ">▇<", ">█<"],
},
```

## 4.5 Clock

The `clock` module displays the current date and time.

**Note:** There are two `clock` implementations:

1. `clock`: Fully consistent with what is written below. This is enabled if either one of the following build time conditions is met:

> 1. C++20 with __cpp_concepts >= 201907 (gcc >=13)
> 2. [date.h](https://github.com/HowardHinnant/date) is installed

2. `simpleclock`: Provides only date time functionality. That's it. Conditions for using: False the first point.

### Config

